/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:27 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/13 13:24:38 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

void	refactor(t_thread *thread)
{
	int	actual_time;
	int	time_refactor;

	pthread_mutex_lock(&thread->values->mut);
	if (!thread->coder->alive)
	{
		pthread_mutex_unlock(&thread->values->mut);
		return ;
	}
	actual_time = get_time_delta(thread->values->start_time);
	time_refactor = thread->values->time_to_refactor;
	printf("%d %d is refactoring\n", actual_time, thread->coder->id);
	pthread_mutex_unlock(&thread->values->mut);
	usleep(time_refactor * 1000);
}
