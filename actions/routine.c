/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:15:10 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/09 17:02:46 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	make_routine(t_thread *thread, int n_times, char *scheduler)
{
	int	n_compiled;
	int	alive;

	pthread_mutex_lock(thread->values->mut);
	alive = thread->coder->alive;
	n_compiled = thread->coder->n_compiled;
	pthread_mutex_unlock(thread->values->mut);
	if (strcmp(scheduler, "edf") == 0)
		edf(thread);
	if (n_compiled >= n_times || !alive)
		return (1);
	if (!take_dongle(thread))
		return (1);
	compile(thread);
	if (!put_dongle_down(thread))
		return (1);
	debug(thread);
	refactor(thread);
	if (alive)
	{
		pthread_mutex_lock(thread->values->mut);
		thread->coder->n_compiled++;
		pthread_mutex_unlock(thread->values->mut);
	}
	return (0);
}

int	routine(t_thread *thread)
{
	int		n_times;
	char	*scheduler;

	if (thread->values->number_of_coders == 1)
		return (0);
	n_times = thread->values->number_of_compiles_required;
	if (thread->coder->id % 2 == 0)
		usleep(thread->values->time_to_compile * 1000);
	pthread_mutex_lock(thread->values->mut);
	scheduler = thread->values->scheduler;
	pthread_mutex_unlock(thread->values->mut);
	while (1)
	{
		if (make_routine(thread, n_times, scheduler))
			break ;
	}
	return (0);
}
