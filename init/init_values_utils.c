/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:02:17 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/09 15:02:39 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

pthread_mutex_t	*init_mutex_values(int size)
{
	pthread_mutex_t	*mut;

	mut = malloc(sizeof(pthread_mutex_t) * size);
	if (!mut)
		return (NULL);
	pthread_mutex_init(mut, NULL);
	return (mut);
}

pthread_t	*init_thread_values(int size)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * size);
	if (!thread)
		return (NULL);
	memset(thread, 0, sizeof(pthread_t) * size);
	return (thread);
}

pthread_cond_t	*init_cond_values(int size)
{
	pthread_cond_t	*cond;

	cond = malloc(sizeof(pthread_cond_t) * size);
	if (!cond)
		return (NULL);
	pthread_cond_init(cond, NULL);
	return (cond);
}

int	init_queue(t_values *values)
{
	values->queue = malloc(sizeof(t_coders *) * values->number_of_coders);
	if (!values)
		return (1);
	return (0);
}
