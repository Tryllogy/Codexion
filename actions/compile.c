/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:46 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/06 17:17:50 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	compile(t_thread *thread)
{
	int	time_compile;
	int	actual_time;

	if (!thread->coder->alive || !thread->coder->dongles[0]
		|| !thread->coder->dongles[1])
		return ;
	actual_time = get_time_delta(thread->values->start_time);
	thread->coder->last_compile_start = actual_time;
	time_compile = thread->values->time_to_compile;
	pthread_mutex_lock(thread->values->mut);
	printf("%d %d is compiling\n", actual_time, thread->coder->id);
	pthread_mutex_unlock(thread->values->mut);
	usleep(time_compile * 1000);
}
