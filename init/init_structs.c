/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:38:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/02 14:06:45 by tchemin          ###   ########.fr       */
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
		dongles[i].available = 1;
		dongles[i].next_available_time = 0;
		dongles[i].id = i;
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
