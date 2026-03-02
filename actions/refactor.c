/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:27 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/02 13:00:27 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void refactor(t_thread *thread)
{
    int actual_time;
    int time_refactor;

    if (!thread->coder->alive)
        return;

    actual_time = get_time_delta(thread->values->start_time);
    time_refactor = thread->values->time_to_refactor;
    thread->coder->last_compile_start = actual_time;
    pthread_mutex_lock(thread->values->m_print);
    printf("%d %d is refactoring\n", actual_time, thread->coder->id);
    pthread_mutex_unlock(thread->values->m_print);
    usleep(time_refactor * 1000);
}
