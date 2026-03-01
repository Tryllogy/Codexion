/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:38:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 15:56:10 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

t_coders *init_coders(t_coders *coders, t_values values)
{
	int i;

	i = 0;
	while (i < values.number_of_coders)
	{
		coders = add_back_coder(coders, new_coder(i, values.dongles,
												  values.number_of_coders));
		i++;
	}
	link_first_last_coders(coders, values.dongles);
	return (coders);
}

int init_values_malloc(t_values *values)
{
	values->dongles = NULL;
	values->coders = NULL;
	values->threads = NULL;
	values->threads_coder = NULL;
	values->thread_monitor = NULL;
	values->dongles = init_dongles(values->dongles, *values);
	if (!values->dongles)
		return (1);
	values->coders = init_coders(values->coders, *values);
	if (!values->coders)
		return (1);
	values->threads = init_threads(values->threads, values);
	if (!values->threads)
		return (1);
	values->threads_coder = malloc(sizeof(pthread_t) * values->number_of_coders);
	if (!values->threads_coder)
		return (1);
	memset(values->threads_coder, 0, sizeof(pthread_t) * values->number_of_coders);
	values->thread_monitor = malloc(sizeof(pthread_t));
	if (!values->thread_monitor)
		return (1);
	memset(values->thread_monitor, 0, sizeof(pthread_t));
	return (0);
}

void init_values(t_values *values, char **argv)
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
	if (init_values_malloc(values))
		return;
	values->start_time.tv_sec = 0;
	values->start_time.tv_usec = 0;
}

t_thread *init_threads(t_thread *threads, t_values *values)
{
	int i;
	t_coders *tmp;

	threads = malloc(sizeof(t_thread) * values->number_of_coders);
	if (!threads)
		return (NULL);
	i = 0;
	tmp = values->coders;
	while (i < values->number_of_coders)
	{
		(&threads[i])->coder = tmp;
		(&threads[i])->values = values;
		i++;
		tmp = tmp->next;
	}
	return (threads);
}

t_dongle *init_dongles(t_dongle *dongles, t_values values)
{
	int i;

	dongles = malloc(sizeof(t_dongle) * values.number_of_coders);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < values.number_of_coders)
	{
		dongles[i].mutex = NULL;
		dongles[i].cond = NULL;
		dongles[i].id = i;
		dongles[i].available = 1;
		dongles[i].mutex = malloc(sizeof(pthread_mutex_t));
		if (dongles[i].mutex)
			pthread_mutex_init(dongles[i].mutex, NULL);
		dongles[i].cond = malloc(sizeof(pthread_cond_t));
		if (dongles[i].cond)
			pthread_cond_init(dongles[i].cond, NULL);
		if (!dongles[i].cond || !dongles[i].mutex)
			return (free_dongle(dongles, &values, i));
		i++;
	}
	return (dongles);
}
