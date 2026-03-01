#include "../coders/coders.h"

int check_malloc(t_values *values)
{
    if (!values->dongles || !values->coders || !values->threads || !values->threads_coder || !values->thread_monitor)
        return (1);
    return (0);
}
