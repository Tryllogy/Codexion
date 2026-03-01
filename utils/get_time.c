#include "../coders/coders.h"

__int64_t get_time_delta(struct timeval start_time)
{
    struct timeval current_time;
    __int64_t time_in_ms;

    gettimeofday(&current_time, NULL);
    time_in_ms = ((__int64_t)(current_time.tv_sec - start_time.tv_sec) * 1000) + ((__int64_t)(current_time.tv_usec - start_time.tv_usec) / 1000);
    return (time_in_ms);
}
