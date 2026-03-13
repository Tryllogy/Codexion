/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:41 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/13 13:24:34 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

void	debug(t_thread *thread)
{
	int	actual_time;
	int	time_debug;

	pthread_mutex_lock(&thread->values->mut);
	time_debug = thread->values->time_to_debug;
	if (!thread->coder->alive)
	{
		pthread_mutex_unlock(&thread->values->mut);
		return ;
	}
	actual_time = get_time_delta(thread->values->start_time);
	printf("%d %d is debuging\n", actual_time, thread->coder->id);
	pthread_mutex_unlock(&thread->values->mut);
	usleep(time_debug * 1000);
}
