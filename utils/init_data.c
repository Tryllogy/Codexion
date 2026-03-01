/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:38:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 15:02:11 by tchemin          ###   ########.fr       */
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
	values->dongles = NULL;
	values->coders = NULL;
	values->dongles = init_dongles(values->dongles, *values);
	values->coders = init_coders(values->coders, *values);
	values->threads = NULL;
	values->threads_coder = NULL;
	values->threads = init_threads(values->threads, values);
	values->threads_coder = malloc(sizeof(pthread_t) * values->number_of_coders);
	if (values->threads_coder)
		memset(values->threads_coder, 0, sizeof(pthread_t) * values->number_of_coders);
	values->start_time.tv_sec = 0;
	values->start_time.tv_usec = 0;
	values->thread_monitor = malloc(sizeof(pthread_t));
	if (values->thread_monitor)
		memset(values->thread_monitor, 0, sizeof(pthread_t));
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
		(&threads[i])->cond = malloc(sizeof(pthread_cond_t));
		if (!(&threads[i])->cond)
		{
			free_threads(threads, values->threads_coder);
			return (NULL);
		}
		pthread_cond_init((&threads[i])->cond, NULL);
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
		dongles[i].id = i;
		dongles[i].available = 1;
		dongles[i].mutex = malloc(sizeof(pthread_mutex_t));
		if (!dongles[i].mutex)
		{
			free_dongle(dongles, values);
			return (NULL);
		}
		pthread_mutex_init(dongles[i].mutex, NULL);
		i++;
	}
	return (dongles);
}
