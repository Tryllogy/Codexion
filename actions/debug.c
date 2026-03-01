/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:41 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 12:42:15 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void debug(t_thread *thread)
{
    int actual_time;
    int time_debug;

    if (!thread->coder->alive || !thread->coder->dongles[0]->available || !thread->coder->dongles[1]->available)
        return;

    actual_time = get_time_delta(thread->values->start_time);
    time_debug = thread->values->time_to_debug;
    thread->coder->last_compile_start = actual_time;
    printf("%d %d is debuging\n", actual_time, thread->coder->id);
    usleep(time_debug * 1000);
}
