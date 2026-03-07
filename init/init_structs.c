/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:38:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/07 17:44:27 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

t_coders	*init_coders(t_coders *coders, t_values values)
{
	int	i;

	coders = malloc(sizeof(t_coders) * values.number_of_coders);
	if (!coders)
		return (NULL);
	i = 0;
	while (i < values.number_of_coders)
	{
		coders[i].id = i + 1;
		coders[i].n_compiled = 0;
		coders[i].alive = 1;
		coders[i].last_compile_start_time = 0;
		coders[i].waiting = 0;
		coders[i].next_burnout_time = 0;
		link_coder_dongle(&coders[i], values, i);
		i++;
	}
	i = 0;
	while (i < values.number_of_coders)
	{
		link_dongle_coder(coders, values, i);
		i++;
	}
	return (coders);
}

t_thread	*init_threads(t_thread *threads, t_values *values)
{
	int			i;
	t_coders	*coders;

	threads = malloc(sizeof(t_thread) * values->number_of_coders);
	if (!threads)
		return (NULL);
	i = 0;
	coders = values->coders;
	while (i < values->number_of_coders)
	{
		(&threads[i])->coder = &coders[i];
		(&threads[i])->values = values;
		i++;
	}
	return (threads);
}

int	init_dongles_malloc(t_dongle *dongle)
{
	dongle->coders[0] = NULL;
	dongle->coders[1] = NULL;
	dongle->mutex = malloc(sizeof(pthread_mutex_t));
	if (dongle->mutex)
		pthread_mutex_init(dongle->mutex, NULL);
	dongle->cond = malloc(sizeof(pthread_cond_t));
	if (dongle->cond)
		pthread_cond_init(dongle->cond, NULL);
	if (!dongle->cond || !dongle->mutex)
		return (1);
	return (0);
}

t_dongle	*init_dongles(t_dongle *dongles, t_values values)
{
	int	i;

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
		if (init_dongles_malloc(&dongles[i]))
			return (free_dongle(dongles, &values, i));
		i++;
	}
	return (dongles);
}
