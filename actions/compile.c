/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:46 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/09 17:43:15 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	compile(t_thread *thread)
{
	__int64_t	time_compile;
	__int64_t	actual_time;

	pthread_mutex_lock(&thread->values->mut);
	if (!thread->coder->alive || !thread->coder->dongles[0]
		|| !thread->coder->dongles[1])
	{
		pthread_mutex_unlock(&thread->values->mut);
		return ;
	}
	actual_time = get_time_delta(thread->values->start_time);
	thread->coder->last_compile_start_time = actual_time;
	time_compile = thread->values->time_to_compile;
	printf("%ld %d is compiling\n", actual_time,
		thread->coder->id);
	thread->coder->burnout = actual_time + time_compile;
	pthread_mutex_unlock(&thread->values->mut);
	usleep(time_compile * 1000);
}
