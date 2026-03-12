/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_dongle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:44:47 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/12 16:27:57 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"
#include <stdio.h>
#include <unistd.h>

void print_dongle_taken(t_thread *thread)
{
	__int64_t actual_time;

	pthread_mutex_lock(&thread->values->mut);
	if (!thread->coder->alive)
	{
		pthread_mutex_unlock(&thread->values->mut);
		return;
	}
	actual_time = get_time_delta(thread->values->start_time);
	printf("%lld %d has taken a dongle\n", (long long)actual_time,
		   thread->coder->id);
	pthread_mutex_unlock(&thread->values->mut);
}

void lock_dongle(t_thread *thread, t_dongle *dongle)
{
	__int64_t actual_time;
	struct timespec ts;

	if (pthread_mutex_lock(&dongle->mutex) != 0)
		return;
	actual_time = get_time_delta(thread->values->start_time);
	while (dongle->available == 0 || actual_time < dongle->next_available_time)
	{
		init_ts(&ts, dongle, actual_time);
		pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
		actual_time = get_time_delta(thread->values->start_time);
	}
	dongle->available = 0;
	actual_time = get_time_delta(thread->values->start_time);
	dongle->next_available_time = actual_time + thread->values->dongle_cooldown;
	dongle->owner = thread->this_thread;
	dongle->owner_set = 1;
	pthread_mutex_unlock(&dongle->mutex);
	print_dongle_taken(thread);
}

int take_dongle(t_thread *thread)
{
	t_dongle *dongle1;
	t_dongle *dongle2;

	if (strcmp(thread->values->scheduler, "edf") == 0)
		wait_for_turn(thread);
	dongle1 = thread->coder->dongles[0];
	dongle2 = thread->coder->dongles[1];
	if (dongle1 < dongle2)
	{
		lock_dongle(thread, dongle1);
		lock_dongle(thread, dongle2);
	}
	else
	{
		lock_dongle(thread, dongle2);
		lock_dongle(thread, dongle1);
	}
	return (1);
}

void unlock_dongle(t_thread *thread, t_dongle *dongle)
{
	__int64_t actual_time;

	if (pthread_mutex_lock(&dongle->mutex) != 0)
		return;
	actual_time = get_time_delta(thread->values->start_time);
	dongle->available = 1;
	dongle->next_available_time = actual_time + thread->values->dongle_cooldown;
	if (dongle->owner_set && thread->this_thread == dongle->owner)
	{
		pthread_cond_broadcast(&dongle->cond);
		dongle->owner_set = 0;
	}
	else
		pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

int put_dongle_down(t_thread *thread)
{
	t_dongle *dongle1;
	t_dongle *dongle2;

	dongle1 = thread->coder->dongles[0];
	dongle2 = thread->coder->dongles[1];
	unlock_dongle(thread, dongle1);
	unlock_dongle(thread, dongle2);
	return (1);
}
