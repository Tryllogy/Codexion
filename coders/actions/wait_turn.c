/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:04:06 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/12 15:39:42 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

static void move_queue(t_coders **queue, int n_in_queue)
{
	int i;

	i = 0;
	while (i < n_in_queue - 1)
	{
		queue[i] = queue[i + 1];
		i++;
	}
}

int is_waiting(t_thread *thread)
{
	int i;
	t_coders **queue;
	t_coders *coder;
	int n_in_queue;

	coder = thread->coder;
	queue = thread->values->queue;
	n_in_queue = thread->values->n_in_queue;
	i = 0;
	while (i < n_in_queue)
	{
		if (coder == queue[i])
			return (1);
		i++;
	}
	return (0);
}

void wait_for_turn(t_thread *thread)
{
	pthread_mutex_lock(&thread->values->sched_mut);
	if (thread->values->n_in_queue <= 0 || !is_waiting(thread))
	{
		pthread_mutex_unlock(&thread->values->sched_mut);
		return;
	}
	while (thread->coder != thread->values->queue[0])
		pthread_cond_wait(&thread->values->sched_cond,
						  &thread->values->sched_mut);
	move_queue(thread->values->queue, thread->values->n_in_queue);
	thread->values->queue[thread->values->n_in_queue - 1] = NULL;
	thread->values->n_in_queue--;
	thread->coder->waiting = 0;
	pthread_cond_broadcast(&thread->values->sched_cond);
	pthread_mutex_unlock(&thread->values->sched_mut);
}
