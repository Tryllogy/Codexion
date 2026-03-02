#include "../coders/coders.h"

void print_dongle_taken(t_thread *thread)
{
    __int64_t actual_time;

    actual_time = get_time_delta(thread->values->start_time);
    pthread_mutex_lock(thread->values->m_print);
    printf("%ld %d has taken a dongle\n", actual_time, thread->coder->id);
    pthread_mutex_unlock(thread->values->m_print);
}

int lock(t_thread *thread, t_dongle *dongle1, t_dongle *dongle2)
{
    if (pthread_mutex_lock(dongle1->mutex) != 0)
        return (0);
    print_dongle_taken(thread);
    if (pthread_mutex_lock(dongle2->mutex) != 0)
    {
        pthread_mutex_unlock(dongle1->mutex);
        return (0);
    }
    print_dongle_taken(thread);
    return (1);
}

int lock_mutex(t_thread *thread)
{
    t_dongle *dongle1;
    t_dongle *dongle2;

    dongle1 = thread->coder->dongles[0];
    dongle2 = thread->coder->dongles[1];

    if (dongle1 < dongle2)
        return (lock(thread, dongle1, dongle2));
    else
        return (lock(thread, dongle2, dongle1));
    return (1);
}

int unlock_mutex(t_thread *thread)
{
    t_dongle *dongle1;
    t_dongle *dongle2;

    dongle1 = thread->coder->dongles[0];
    dongle2 = thread->coder->dongles[1];

    usleep(thread->values->dongle_cooldown * 1000);
    if (pthread_mutex_unlock(dongle1->mutex) != 0)
        return (0);
    if (pthread_mutex_unlock(dongle2->mutex) != 0)
    {
        pthread_mutex_unlock(dongle1->mutex);
        return (0);
    }
    return (1);
}
