/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:43:12 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/12 15:39:42 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

void sort_queue(t_coders **queue, int n_in_queue)
{
	t_coders *coder_tmp;
	int i;
	int j;

	if (n_in_queue == 1)
		return;
	i = 0;
	while (i < n_in_queue)
	{
		j = 0;
		while (j < n_in_queue)
		{
			if (queue[i]->burnout < queue[j]->burnout)
			{
				coder_tmp = queue[j];
				queue[j] = queue[i];
				queue[i] = coder_tmp;
			}
			j++;
		}
		i++;
	}
}

t_coders *edf(t_thread *thread)
{
	int n_in_queue;

	pthread_mutex_lock(&thread->values->sched_mut);
	n_in_queue = thread->values->n_in_queue;
	thread->coder->waiting = 1;
	if (n_in_queue >= thread->values->number_of_coders)
	{
		pthread_mutex_unlock(&thread->values->sched_mut);
		return (NULL);
	}
	thread->values->queue[n_in_queue] = thread->coder;
	thread->values->n_in_queue = n_in_queue + 1;
	sort_queue(thread->values->queue, n_in_queue + 1);
	pthread_mutex_unlock(&thread->values->sched_mut);
	return (NULL);
}
