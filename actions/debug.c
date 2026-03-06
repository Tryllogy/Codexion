/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:41 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/06 17:17:48 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	debug(t_thread *thread)
{
	int	actual_time;
	int	time_debug;

	if (!thread->coder->alive)
		return ;
	actual_time = get_time_delta(thread->values->start_time);
	time_debug = thread->values->time_to_debug;
	thread->coder->last_compile_start = actual_time;
	pthread_mutex_lock(thread->values->mut);
	printf("%d %d is debuging\n", actual_time, thread->coder->id);
	pthread_mutex_unlock(thread->values->mut);
	usleep(time_debug * 1000);
}
