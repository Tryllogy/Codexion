/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:02:17 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/11 17:10:26 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

pthread_t	*init_thread_values(int size)
{
	pthread_t	*thread;

	thread = malloc(sizeof(pthread_t) * size);
	if (!thread)
		return (NULL);
	memset(thread, 0, sizeof(pthread_t) * size);
	return (thread);
}

int	init_queue(t_values *values)
{
	values->queue = malloc(sizeof(t_coders *) * values->number_of_coders);
	if (!values->queue)
		return (1);
	return (0);
}
