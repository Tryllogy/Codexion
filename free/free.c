#include "../coders/coders.h"

void free_coders(t_coders *coders, int n_coders)
{
    int i;
    t_coders *tmp;

    if (!coders)
        return;
    i = 0;
    while (i < n_coders)
    {
        tmp = coders->next;
        if (coders)
            free(coders);
        coders = tmp;
        i++;
    }
}

int free_threads(t_thread *threads, pthread_t *thread_coder)
{
    if (threads)
        free(threads);
    if (thread_coder)
        free(thread_coder);
    return (1);
}

int free_mutex(t_dongle *dongles, t_values values)
{
    int i;

    i = 0;
    while (i < values.number_of_coders)
    {
        pthread_mutex_destroy(dongles[i].mutex);
        if (dongles[i].mutex)
            free(dongles[i].mutex);
        i++;
    }
    return (1);
}
