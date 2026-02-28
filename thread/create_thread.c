/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/28 21:53:34 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void lock_mutex(t_dongle *dongles[2])
{
	pthread_mutex_lock(dongles[0]->mutex);
	pthread_mutex_lock(dongles[1]->mutex);
}

void unlock_mutex(t_dongle *dongles[2])
{
	pthread_mutex_unlock(dongles[0]->mutex);
	pthread_mutex_unlock(dongles[1]->mutex);
}

int routine(t_thread *thread)
{
	int n_times;

	while (!thread->values->start_time.tv_sec)
		usleep(10);
	n_times = thread->values->number_of_compiles_required;
	while (thread->coder->n_compiled < n_times && thread->coder->alive)
	{
		if (thread->coder->dongles[0]->available && thread->coder->dongles[1]->available)
		{
			lock_mutex(thread->coder->dongles);
			compile(thread);
			unlock_mutex(thread->coder->dongles);
		}
		else
			continue;
		debug(thread);
		refactor(thread);
		if (thread->coder->alive)
			(thread->coder->n_compiled)++;
	}
	if (!thread->coder->alive)
	{ // burnout();
	}
	return (0);
}

int create_threads(t_values *values)
{
	int i;
	int finished;

	if (!values->threads_coder || !values->threads)
		return (free_threads(values->threads, values->threads_coder));
	i = 0;
	finished = 0;
	while (i < values->number_of_coders)
	{
		if (pthread_create(&values->threads_coder[i], NULL, (void *)routine,
						   &values->threads[i]) != 0)
			return (1);
		i++;
	}
	finished++;
	if (finished == values->number_of_coders)
		values->finished = 1;
	return (0);
}
