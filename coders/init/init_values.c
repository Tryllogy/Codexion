/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:56:26 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/12 15:39:42 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

int init_values_malloc(t_values *values)
{
	if (pthread_mutex_init(&values->mut, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&values->sched_mut, NULL) != 0)
		return (1);
	if (pthread_cond_init(&values->sched_cond, NULL) != 0)
		return (1);
	values->dongles = init_dongles(values->dongles, *values);
	if (!values->dongles)
		return (1);
	values->coders = init_coders(values->coders, *values);
	if (!values->coders)
		return (1);
	values->threads = init_threads(values->threads, values);
	if (!values->threads)
		return (1);
	values->threads_coder = init_thread_values(values->number_of_coders);
	if (!values->threads_coder)
		return (1);
	values->thread_monitor = init_thread_values(1);
	if (!values->thread_monitor)
		return (1);
	return (0);
}

int init_values(t_values *values, char **argv)
{
	values->number_of_coders = atoi(argv[1]);
	values->time_to_burnout = atoi(argv[2]);
	values->time_to_compile = atoi(argv[3]);
	values->time_to_debug = atoi(argv[4]);
	values->time_to_refactor = atoi(argv[5]);
	values->number_of_compiles_required = atoi(argv[6]);
	values->dongle_cooldown = atoi(argv[7]);
	values->scheduler = argv[8];
	values->finished = 0;
	values->id_next_coder = 0;
	values->n_in_queue = 0;
	values->dongles = NULL;
	values->coders = NULL;
	values->threads = NULL;
	values->threads_coder = NULL;
	values->thread_monitor = NULL;
	values->queue = NULL;
	if (init_values_malloc(values))
		return (1);
	values->start_time.tv_sec = 0;
	values->start_time.tv_usec = 0;
	return (0);
}
