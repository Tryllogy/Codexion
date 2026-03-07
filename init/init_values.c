/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:56:26 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/07 18:08:32 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

static pthread_mutex_t	*init_mutex_values(int size)
{
	pthread_mutex_t	*mut;

	mut = malloc(sizeof(pthread_mutex_t) * size);
	if (!mut)
		return (NULL);
	pthread_mutex_init(mut, NULL);
	return (mut);
}

static pthread_t	*init_thread_values(int size)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * size);
	if (!thread)
		return (NULL);
	memset(thread, 0, sizeof(pthread_t) * size);
	return (thread);
}

static pthread_cond_t	*init_cond_values(int size)
{
	pthread_cond_t	*cond;

	cond = malloc(sizeof(pthread_cond_t) * size);
	if (!cond)
		return (NULL);
	pthread_cond_init(cond, NULL);
	return (cond);
}

int	init_values_malloc(t_values *values)
{
	values->mut = init_mutex_values(1);
	if (!values->mut)
		return (1);
	values->sched_mut = init_mutex_values(1);
	if (!values->sched_mut)
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
	values->sched_cond = init_cond_values(1);
	if (!values->sched_cond)
		return (1);
	return (0);
}

int	init_values(t_values *values, char **argv)
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
	values->dongles = NULL;
	values->coders = NULL;
	values->threads = NULL;
	values->threads_coder = NULL;
	values->thread_monitor = NULL;
	values->mut = NULL;
	values->sched_mut = NULL;
	values->sched_cond = NULL;
	if (init_values_malloc(values))
		return (1);
	values->start_time.tv_sec = 0;
	values->start_time.tv_usec = 0;
	return (0);
}
