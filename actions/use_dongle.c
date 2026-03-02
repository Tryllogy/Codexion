#include "../coders/coders.h"
#include <sys/time.h>

void print_dongle_taken(t_thread *thread)
{
    __int64_t actual_time;

    if (!thread->coder->alive)
        return;

    actual_time = get_time_delta(thread->values->start_time);
    pthread_mutex_lock(thread->values->m_print);
    printf("%ld %d has taken a dongle\n", actual_time, thread->coder->id);
    pthread_mutex_unlock(thread->values->m_print);
}

void lock_dongle(t_thread *thread, t_dongle *dongle)
{
    __int64_t actual_time;
    struct timespec ts;

    if (pthread_mutex_lock(dongle->mutex) != 0)
        return;
    actual_time = get_time_delta(thread->values->start_time);
    while (dongle->available == 0 || actual_time < dongle->next_available_time)
    {
        init_ts(&ts, dongle, actual_time);
        pthread_cond_timedwait(dongle->cond, dongle->mutex, &ts);
        actual_time = get_time_delta(thread->values->start_time);
    }
    dongle->available = 0;
    actual_time = get_time_delta(thread->values->start_time);
    dongle->next_available_time = actual_time + thread->values->dongle_cooldown;
    print_dongle_taken(thread);
    pthread_mutex_unlock(dongle->mutex);
}

int take_dongle(t_thread *thread)
{
    t_dongle *dongle1;
    t_dongle *dongle2;

    dongle1 = thread->coder->dongles[0];
    dongle2 = thread->coder->dongles[1];

    if (dongle1 < dongle2)
    {
        lock_dongle(thread, dongle1);
        lock_dongle(thread, dongle2);
    }
    else
    {
        lock_dongle(thread, dongle2);
        lock_dongle(thread, dongle1);
    }
    return (1);
}

void unlock_dongle(t_thread *thread, t_dongle *dongle)
{
    __int64_t actual_time;

    actual_time = get_time_delta(thread->values->start_time);
    pthread_mutex_lock(dongle->mutex);
    dongle->available = 1;
    dongle->next_available_time = actual_time + thread->values->dongle_cooldown;
    pthread_cond_broadcast(dongle->cond);
    pthread_mutex_unlock(dongle->mutex);
}

int put_dongle_down(t_thread *thread)
{
    t_dongle *dongle1;
    t_dongle *dongle2;

    dongle1 = thread->coder->dongles[0];
    dongle2 = thread->coder->dongles[1];
    unlock_dongle(thread, dongle1);
    unlock_dongle(thread, dongle2);
    return (1);
}
