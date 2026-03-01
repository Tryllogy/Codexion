#include "../coders/coders.h"

int lock_mutex(t_thread *thread)
{
    t_dongle *dongle1 = thread->coder->dongles[0];
    t_dongle *dongle2 = thread->coder->dongles[1];

    if (!dongle1->available || !dongle2->available)
        return (0);

    if (pthread_mutex_lock(dongle1->mutex) != 0)
        return (0);
    dongle1->available = 0;
    if (pthread_mutex_lock(dongle2->mutex) != 0)
    {
        pthread_mutex_unlock(dongle1->mutex);
        dongle1->available = 1;
        return (0);
    }
    dongle2->available = 0;
    return (1);
}

int unlock_mutex(t_thread *thread)
{
    t_dongle *dongle1 = thread->coder->dongles[0];
    t_dongle *dongle2 = thread->coder->dongles[1];

    if (dongle1->available || dongle2->available)
        return (0);

    usleep(thread->values->dongle_cooldown * 1000);
    if (pthread_mutex_unlock(dongle1->mutex) != 0)
        return (0);
    if (pthread_mutex_unlock(dongle2->mutex) != 0)
    {
        pthread_mutex_unlock(dongle1->mutex);
        return (0);
    }
    dongle1->available = 1;
    dongle2->available = 1;
    return (1);
}
