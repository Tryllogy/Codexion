#include "../coders/coders.h"

int init_values_malloc(t_values *values)
{
    values->m_print = malloc(sizeof(pthread_mutex_t));
    if (!values->m_print)
        return (1);
    pthread_mutex_init(values->m_print, NULL);
    values->dongles = init_dongles(values->dongles, *values);
    if (!values->dongles)
        return (1);
    values->coders = init_coders(values->coders, *values);
    if (!values->coders)
        return (1);
    values->threads = init_threads(values->threads, values);
    if (!values->threads)
        return (1);
    values->threads_coder = malloc(sizeof(pthread_t) * values->number_of_coders);
    if (!values->threads_coder)
        return (1);
    memset(values->threads_coder, 0, sizeof(pthread_t) * values->number_of_coders);
    values->thread_monitor = malloc(sizeof(pthread_t));
    if (!values->thread_monitor)
        return (1);
    memset(values->thread_monitor, 0, sizeof(pthread_t));
    return (0);
}

void init_values(t_values *values, char **argv)
{
    values->number_of_coders = atoi(argv[1]);
    values->time_to_burnout = atoi(argv[2]);
    values->time_to_compile = atoi(argv[3]);
    values->time_to_debug = atoi(argv[4]);
    values->time_to_refactor = atoi(argv[5]);
    values->number_of_compiles_required = atoi(argv[6]);
    values->dongle_cooldown = atoi(argv[7]);
    values->scheduler = argv[8];
    values->finished = 0;
    values->dongles = NULL;
    values->coders = NULL;
    values->threads = NULL;
    values->threads_coder = NULL;
    values->thread_monitor = NULL;
    if (init_values_malloc(values))
        return;
    values->start_time.tv_sec = 0;
    values->start_time.tv_usec = 0;
}
