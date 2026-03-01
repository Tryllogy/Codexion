/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 15:09:52 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int routine(t_thread *thread)
{
	int n_times;

	if (thread->values->number_of_coders == 1)
		return (0);
	n_times = thread->values->number_of_compiles_required;
	if (thread->coder->id % 2 == 0)
		usleep(thread->values->time_to_compile * 1000 * 2);
	while (thread->coder->n_compiled < n_times && thread->coder->alive)
	{
		if (thread->coder->dongles[0]->available && thread->coder->dongles[1]->available)
		{
			if (!lock_mutex(thread))
				return (1);
			compile(thread);
			if (!unlock_mutex(thread))
				return (1);
			debug(thread);
			refactor(thread);
			if (thread->coder->alive)
				(thread->coder->n_compiled)++;
		}
	}
	return (0);
}

void monitor(t_values *values)
{
	t_coders *tmp;
	__int64_t time_delta;
	__int64_t burned_out;
	int i;

	tmp = values->coders;
	while (!values->finished)
	{
		time_delta = get_time_delta(values->start_time) - tmp->last_compile_start;
		if (tmp->alive && time_delta > values->time_to_burnout && tmp->n_compiled < values->number_of_compiles_required)
		{
			burned_out = get_time_delta(values->start_time);
			tmp->alive = 0;
			printf("%ld %d burned out\n", burned_out, tmp->id);
			i = 0;
			while (i < values->number_of_coders)
			{
				tmp->alive = 0;
				tmp = tmp->next;
				i++;
			}
		}
		tmp = tmp->next;
	}
}

int create_threads(t_values *values)
{
	int i;

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
	if (pthread_create(&*values->thread_monitor, NULL, (void *)monitor, values) != 0)
		return (1);
	return (0);
}
