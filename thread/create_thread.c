/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/06 17:18:16 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	routine(t_thread *thread)
{
	int	n_times;

	if (thread->values->number_of_coders == 1)
		return (0);
	n_times = thread->values->number_of_compiles_required;
	if (thread->coder->id % 2 == 0)
		usleep(thread->values->time_to_compile * 1000);
	while (thread->coder->n_compiled < n_times && thread->coder->alive)
	{
		if (!take_dongle(thread))
			return (1);
		compile(thread);
		if (!put_dongle_down(thread))
			return (1);
		debug(thread);
		refactor(thread);
		if (thread->coder->alive)
		{
			pthread_mutex_lock(thread->values->mut);
			(thread->coder->n_compiled)++;
			pthread_mutex_unlock(thread->values->mut);
		}
	}
	return (0);
}

int	finish(t_values *values, int id)
{
	int			i;
	__int64_t	burned_out;

	burned_out = get_time_delta(values->start_time);
	pthread_mutex_lock(values->mut);
	printf("%ld %d burned out\n", burned_out, values->coders[id].id);
	i = 0;
	while (i < values->number_of_coders)
	{
		values->coders[i].alive = 0;
		i++;
	}
	values->finished = 1;
	pthread_mutex_unlock(values->mut);
	return (1);
}

void	monitor_burnout(t_values *values)
{
	t_coders	*coders;
	int			i;
	__int64_t	time_delta;
	int			is_finished;

	pthread_mutex_lock(values->mut);
	is_finished = !values->finished;
	pthread_mutex_unlock(values->mut);
	coders = values->coders;
	while (!is_finished)
	{
		i = 0;
		while (i < values->number_of_coders)
		{
			time_delta = get_time_delta(values->start_time)
				- coders[i].last_compile_start;
			if (coders[i].alive && time_delta > values->time_to_burnout
				&& coders[i].n_compiled < values->number_of_compiles_required)
				is_finished = finish(values, i);
			i++;
		}
	}
}

int	create_threads(t_values *values)
{
	int	i;

	if (!values->threads_coder || !values->threads)
		return (free_threads(values->threads, values->threads_coder));
	i = 0;
	while (i < values->number_of_coders)
	{
		if (pthread_create(&values->threads_coder[i], NULL, (void *)routine,
				&values->threads[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&*values->thread_monitor, NULL, (void *)monitor_burnout,
			values) != 0)
		return (1);
	return (0);
}
