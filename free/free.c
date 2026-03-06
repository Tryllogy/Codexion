/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:05:06 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/06 17:17:59 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	free_coders(t_coders *coders)
{
	if (!coders)
		return ;
	free(coders);
}

int	free_threads(t_thread *threads, pthread_t *thread_coder)
{
	if (threads)
		free(threads);
	if (thread_coder)
		free(thread_coder);
	return (1);
}

void	*free_dongle(t_dongle *dongles, t_values *values, int n_dongles)
{
	int	i;

	values = (t_values *)values;
	if (!dongles)
		return (NULL);
	i = 0;
	while (i <= n_dongles && i < values->number_of_coders)
	{
		if (dongles[i].mutex)
		{
			pthread_mutex_destroy(dongles[i].mutex);
			free(dongles[i].mutex);
			dongles[i].mutex = NULL;
		}
		if (dongles[i].cond)
		{
			pthread_cond_destroy(dongles[i].cond);
			free(dongles[i].cond);
			dongles[i].cond = NULL;
		}
		i++;
	}
	free(dongles);
	return (NULL);
}
