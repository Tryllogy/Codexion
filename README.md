*This project has been created as part of the 42 curriculum by tchemin.*

**Project: Manipulating threads, mutexes and condition variables in C.**

## Table of contents
- [Description](#description)
    - [Goal](#goal)
    - [Overview](#overview)
- [Instructions](#instructions)
    - [How to compile](#how-to-compile)
    - [How to execute](#how-to-execute)
- [Example run](#example-run)
- [Blocking cases handled](#blocking-cases-handled)
    - [Deadlock prevention](#deadlock-prevention)
    - [Cooldown handling](#cooldown-handling)
    - [Burnout detection](#burnout-detection)
    - [Log serialization](#log-serialization)
    - [Starvation prevention](#starvation-prevention)
- [Thread synchronization mechanisms](#thread-synchronization-mechanisms)
- [Resources](#resources)
- [Notes](#notes)

## Description

### Goal

The project implements threads that synchronize using mutexes and condition variables to protect shared data.

There are **N coders** (N threads). Each coder must take **two dongles** to perform a compile operation. Dongles are **exclusive** resources and become **unavailable** for a cooldown period after use.

### Overview

What happens when executing the program:

1. The program creates **N coder threads**.
2. It creates a **monitor thread** that detects if a coder **burns out**.
3. Each coder **repeats** the following for at least `<number_of_compiles_required>` times:
     - **Compile** (requires acquiring two dongles)
     - **Debug** (debugging time)
     - **Refactor** (refactor time)

Rules and behavior:
- A coder can compile **only** when they hold both required dongles (right and left).
- Dongles are **exclusive** while a coder is compiling.
- After a compilation finishes, the dongles remain **unavailable** for the configured cooldown.
- If a coder burns out **while compiling/debugging/refactoring**, the simulation stops.
- When all coders finish the required number of compilations, the program exits.

Because of **thread scheduling** and **machine performance**, running the program multiple times with the same arguments can produce **different interleavings and outputs**.

## Instructions

### How to compile

Use the Makefile:

- `make` — compile all files
- `make clean` — remove build artefacts
- `make fclean` — clean and remove the binary (`codexion`)
- `make re` — recompile

### How to execute

- `make run MODE='edf'` or `make run MODE='fifo'`
- Or run directly:

```Shell
./codexion <number_of_coders> <time_to_burnout> <time_to_compile><time_to_debug> <time_to_refactor> <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

Constraints:
- `number_of_coders` must be > 0
- All timings are in milliseconds and must be >= 0
- `scheduler` must be `fifo` or `edf`

## Example run

INPUT:
```
./codexion 4 800 200 200 200 1 100 fifo
```

Possible OUTPUT (example):
```
0 3 has taken a dongle
0 3 has taken a dongle
0 3 is compiling
2 1 has taken a dongle
9 1 has taken a dongle
9 1 is compiling
200 3 is debugging
209 1 is debugging
300 4 has taken a dongle
309 4 has taken a dongle
309 4 is compiling
309 2 has taken a dongle
309 2 has taken a dongle
309 2 is compiling
402 3 is refactoring
410 1 is refactoring
509 4 is debugging
509 2 is debugging
610 3 has taken a dongle
610 3 has taken a dongle
610 3 is compiling
610 1 has taken a dongle
610 1 has taken a dongle
610 1 is compiling
709 2 is refactoring
709 4 is refactoring
810 3 is debugging
810 1 is debugging
910 2 has taken a dongle
910 2 has taken a dongle
910 2 is compiling
910 4 has taken a dongle
910 4 has taken a dongle
910 4 is compiling
1010 3 is refactoring
1010 1 is refactoring
1109 2 is debugging
1109 4 is debugging
1309 2 is refactoring
1310 4 is refactoring
```

## Blocking cases handled

### Deadlock prevention
What is a deadlock:

A deadlock (interblocage) is a situation where two or more threads are permanently blocked because each waits for a resource held by another. In concurrent systems the four Coffman conditions must hold simultaneously for a deadlock to be possible:

- Mutual exclusion: at least one resource is non-shareable (only one thread can use it at a time).
- Hold and wait: a thread holds at least one resource while waiting to acquire additional resources.
- No preemption: resources cannot be forcibly taken from a thread; they are released only voluntarily.
- Circular wait: there exists a cycle of threads each waiting for a resource held by the next thread in the cycle.

To prevent deadlocks we break at least one of these conditions. In this project the main measures are:

- Enforced resource ordering: when a coder must acquire two dongles, it does so in a deterministic order (e.g. the dongle with the lower index is locked first, then the higher index). This breaks the circular-wait condition and is a simple, effective solution similar to standard dining-philosophers fixes.

### Cooldown handling
To make the cooldown on the use of a dongle, I used
```C
pthread_cond_timedwait()
```
With this function, I can make a coder that request the dongle waiting for it to be available by waiting `<dongle_cooldown>`

The cooldown is implemented by marking a dongle unavailable for a fixed period after it has been used, and waking waiting threads with `pthread_cond_broadcast()` (or `pthread_cond_signal()`) when the cooldown expires. Using `pthread_cond_timedwait()` prevents busy-waiting and keeps the CPU usage low.

### Burnout detection
Using the **monitoring thread**, I can calculate the time of each coder from their **last compilation**.
If a the time is **superior** to `<time_to_burnout>` it means the coder has burned out.

### Log serialization
Each print is **secured** by locking a mutex preventing all coders AND the monitoring to print at the same time. (see: Thread synchronization mechanisms below)

### Starvation prevention
Starvation happens when a thread never obtains the resources it needs because other threads repeatedly take them first. To mitigate starvation in this project:

- The scheduler selection (`fifo` or `edf`) controls which coder is eligible to run next and reduces unfair interleavings that could starve a coder.
- The monitor can detect long waits (burnout) and stop the simulation rather than letting a thread wait forever — this is primarily a safety/termination mechanism for the exercise.

## Thread synchronization mechanisms

This project uses the POSIX threading primitives to coordinate access to shared resources (dongles, logging) and to implement the monitoring/termination behaviour.

Primitives used
- `pthread_mutex_t` — a mutex is used per dongle to protect the dongle's internal state (available/unavailable, cooldown timing). A separate mutex is used to serialize printing so output lines do not interleave.
- `pthread_cond_t` — each dongle exposes a condition variable used to block threads that wait for the dongle to become available (or for the cooldown to finish). Waiters call `pthread_cond_timedwait()` or `pthread_cond_wait()` while holding the dongle mutex.
- `pthread_cond_timedwait()` — used to implement cooldown delays (a thread can sleep until the dongle exits cooldown or a timeout occurs).

How these primitives coordinate shared access
- Acquire sequence for using two dongles:
    1. Determine acquisition order (for example by dongle index): `first = min(left, right); second = max(left, right)`.
    2. `pthread_mutex_lock(&dongles[first].mutex)` — inspect state and wait on `dongles[first].cond` if needed.
    3. `pthread_mutex_lock(&dongles[second].mutex)` — now holding both mutexes the coder can mark both dongles as taken and start compiling.
    4. After compiling, mark dongles unavailable for the cooldown period, call `pthread_cond_broadcast(&dongles[i].cond)` (under the mutex) when their cooldown ends, then `pthread_mutex_unlock()`.

Example: safe wait/use/release cycle (conceptual)

1. To wait for a dongle safely:

    - `pthread_mutex_lock(&d->mutex);`
    - while (d->in_use || in_cooldown) `pthread_cond_timedwait(&d->cond, &d->mutex, &timeout);`
    - mark `d->in_use = true;`
    - `pthread_mutex_unlock(&d->mutex);`

2. To release a dongle and start cooldown:

    - `pthread_mutex_lock(&d->mutex);`
    - mark `d->in_use = false;` and set `d->cooldown_expire = now + cooldown_ms;`
    - call `pthread_cond_broadcast(&d->cond);` to wake waiting threads (still under mutex)
    - `pthread_mutex_unlock(&d->mutex);`

Why holding the mutex during `pthread_cond_broadcast()` matters
- POSIX recommends that the condition predicate and the associated state be protected by the same mutex. Broadcasting while holding the mutex avoids races where a waiter might miss the wakeup because it examined the predicate between the state change and the broadcast.

Monitor and coder communication
- The monitor thread checks each coder's `last_compilation` timestamp under an appropriate mutex (the same structure used by the coder to update that timestamp) and decides if a coder burned out. The monitor can then set a global stop flag (protected by a mutex) and signal all threads to exit.

Race prevention and correctness notes
- All shared mutable state is modified only while holding its protecting mutex. Condition waits use a predicate loop (`while (condition_not_met) pthread_cond_wait(...)`) to be correct under spurious wakeups.
- Wherever possible the code limits the time a thread holds multiple mutexes (acquire only what is necessary and release promptly) to reduce contention and make reasoning about deadlocks easier.
- For debugging and verification, tools such as Helgrind/Valgrind or ThreadSanitizer are useful to detect races and incorrect condition/mutex usage; small owner-tracking assertions can be temporarily added to prove invariants during debugging.

## Resources

### References
- Articles and tutorials about threads and mutexes (examples):
    - Stack Overflow
    - https://www.codequoi.com/threads-mutex-et-programmation-concurrente-en-c/
    - https://perso.ens-lyon.fr/francois.schwarzentruber/teaching/l3-prog/book/c_thread.html

### AI usage
- Debugging with Helgrind (thread resource checks) and logic used to design the EDF scheduler. All code in the project was written by tchemin.

## Notes

- This project is an exercise in concurrent programming and debugging multi-threaded programs.
- For debugging I used Valgrind/Helgrind to find races related to pthread condition/mutex usage. Remove or disable debug instrumentation before performance testing.
