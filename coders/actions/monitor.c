/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:16:00 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/12 15:39:42 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

int finish(t_values *values, int id)
{
	int i;
	__int64_t burned_out;

	pthread_mutex_lock(&values->mut);
	burned_out = get_time_delta(values->start_time);
	printf("%ld %d burned out\n", burned_out, values->coders[id].id);
	i = 0;
	while (i < values->number_of_coders)
	{
		values->coders[i].alive = 0;
		i++;
	}
	values->finished = 1;
	pthread_mutex_unlock(&values->mut);
	return (1);
}

int make_monitor(t_coders *coders, t_values *values)
{
	int i;
	int n_compiled;
	int alive;
	__int64_t time_delta;
	__int64_t last_start;

	i = 0;
	while (i < values->number_of_coders)
	{
		pthread_mutex_lock(&values->mut);
		alive = coders[i].alive;
		n_compiled = coders[i].n_compiled;
		last_start = coders[i].last_compile_start_time;
		pthread_mutex_unlock(&values->mut);
		time_delta = get_time_delta(values->start_time) - last_start;
		if (alive && n_compiled < values->number_of_compiles_required && time_delta > values->time_to_burnout)
			return (finish(values, i));
		i++;
	}
	return (0);
}

void monitor_burnout(t_values *values)
{
	t_coders *coders;
	int is_finished;

	is_finished = set_finish(values);
	coders = values->coders;
	while (!is_finished)
	{
		if (make_monitor(coders, values))
			return;
		is_finished = set_finish(values);
	}
}
