#include "../coders/coders.h"

int get_time(struct timeval start_time)
{
    struct timeval current_time;
    int time_in_ms;

    gettimeofday(&current_time, NULL);
    time_in_ms = ((current_time.tv_sec - start_time.tv_sec) * 1000) + ((current_time.tv_usec - start_time.tv_usec) / 1000);
    return (time_in_ms);
}
