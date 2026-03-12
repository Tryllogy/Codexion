/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:06 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/12 15:39:42 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

void free_coders(t_coders *coders)
{
	if (!coders)
		return;
	free(coders);
}

int free_threads(t_thread *threads, pthread_t *thread_coder)
{
	if (threads)
		free(threads);
	if (thread_coder)
		free(thread_coder);
	return (1);
}

void *free_dongle(t_dongle *dongles, t_values *values, int n_dongles)
{
	int i;

	values = (t_values *)values;
	if (!dongles)
		return (NULL);
	i = 0;
	while (i <= n_dongles && i < values->number_of_coders)
	{
		pthread_mutex_destroy(&dongles[i].mutex);
		pthread_cond_destroy(&dongles[i].cond);
		i++;
	}
	free(dongles);
	return (NULL);
}
