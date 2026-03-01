#include "../coders/coders.h"

int lock_mutex(t_dongle *dongles[2])
{
    if (!dongles[0]->available || !dongles[1]->available)
        return (0);

    if (pthread_mutex_lock(dongles[0]->mutex) != 0)
        return (0);
    dongles[0]->available = 0;
    if (pthread_mutex_lock(dongles[1]->mutex) != 0)
    {
        pthread_mutex_unlock(dongles[0]->mutex);
        dongles[0]->available = 1;
        return (0);
    }
    dongles[1]->available = 0;
    return (1);
}

int unlock_mutex(t_dongle *dongles[2], t_values *values)
{
    if (dongles[0]->available || dongles[1]->available)
        return (0);

    usleep(values->dongle_cooldown * 1000);
    if (pthread_mutex_unlock(dongles[0]->mutex) != 0)
        return (0);
    if (pthread_mutex_unlock(dongles[1]->mutex) != 0)
    {
        pthread_mutex_unlock(dongles[0]->mutex);
        return (0);
    }
    dongles[0]->available = 1;
    dongles[1]->available = 1;
    return (1);
}
