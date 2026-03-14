/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_turn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 15:04:06 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/14 16:54:08 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

static void	set_first_second(t_thread *thread, t_dongle *first,
		t_dongle *second)
{
	t_dongle	*d0;
	t_dongle	*d1;

	d0 = thread->coder->dongles[0];
	d1 = thread->coder->dongles[1];
	if (d0 < d1)
	{
		first = d0;
		second = d1;
	}
	else
	{
		first = d1;
		second = d0;
	}
}

int	check_cond(t_dongle *first, t_dongle *second, t_thread *thread)
{
	if ((first->id_coder_promised == 0
			|| first->id_coder_promised == thread->coder->id)
		&& (second->id_coder_promised == 0
			|| second->id_coder_promised == thread->coder->id))
		return (1);
	return (0);
}

static int	try_reserve_both_dongles(t_thread *thread)
{
	t_dongle	*first;
	t_dongle	*second;

	first = thread->coder->dongles[0];
	second = thread->coder->dongles[1];
	set_first_second(thread, first, second);
	pthread_mutex_lock(&first->mutex);
	pthread_mutex_lock(&second->mutex);
	if (check_cond(first, second, thread))
	{
		first->id_coder_promised = thread->coder->id;
		second->id_coder_promised = thread->coder->id;
		pthread_mutex_unlock(&second->mutex);
		pthread_mutex_unlock(&first->mutex);
		move_queue(thread->values->queue, thread->values->n_in_queue);
		thread->values->queue[thread->values->n_in_queue - 1] = NULL;
		thread->values->n_in_queue--;
		thread->coder->waiting = 0;
		pthread_cond_broadcast(&thread->values->sched_cond);
		return (1);
	}
	pthread_mutex_unlock(&second->mutex);
	pthread_mutex_unlock(&first->mutex);
	return (0);
}

static void	requeue_and_wait(t_thread *thread)
{
	move_queue(thread->values->queue, thread->values->n_in_queue);
	thread->values->queue[thread->values->n_in_queue - 1] = thread->coder;
	pthread_cond_broadcast(&thread->values->sched_cond);
	while (thread->coder != thread->values->queue[0])
		pthread_cond_wait(&thread->values->sched_cond,
			&thread->values->sched_mut);
}

void	wait_for_turn(t_thread *thread)
{
	pthread_mutex_lock(&thread->values->sched_mut);
	if (thread->values->n_in_queue <= 0 || !is_waiting(thread))
	{
		pthread_mutex_unlock(&thread->values->sched_mut);
		return ;
	}
	while (thread->coder != thread->values->queue[0])
		pthread_cond_wait(&thread->values->sched_cond,
			&thread->values->sched_mut);
	while (1)
	{
		if (try_reserve_both_dongles(thread))
			break ;
		else
			requeue_and_wait(thread);
	}
	pthread_mutex_unlock(&thread->values->sched_mut);
}
