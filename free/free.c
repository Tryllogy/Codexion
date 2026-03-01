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

void *free_dongle(t_dongle *dongles, t_values *values, int n_dongles)
{
    int i;
    values = (t_values *)values;
    if (!dongles)
        return (NULL);
    i = 0;
    while (i <= n_dongles && i < values->number_of_coders)
    {
        if (dongles[i].mutex)
        {
            pthread_mutex_destroy(dongles[i].mutex);
            free(dongles[i].mutex);
            dongles[i].mutex = NULL;
        }
        if (dongles[i].cond)
        {
            pthread_cond_destroy(dongles[i].cond);
            free(dongles[i].cond);
            dongles[i].cond = NULL;
        }
        i++;
    }
    free(dongles);
    return (NULL);
}
