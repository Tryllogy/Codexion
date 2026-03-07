/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 16:43:12 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/07 18:49:36 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

t_coders	*edf(t_thread *thread)
{
	__int64_t	deadline;
	int id_coder;

	pthread_mutex_lock(thread->values->sched_mut);
	deadline = thread->coder->last_compile_start
		+ thread->values->time_to_burnout;
	pthread_mutex_unlock(thread->values->sched_mut);
	
	return (NULL);
}
