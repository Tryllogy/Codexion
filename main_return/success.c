/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:22:07 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/07 17:58:42 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	success(t_values *values)
{
	free_coders(values->coders);
	free_dongle(values->dongles, values, values->number_of_coders);
	free_threads(values->threads, values->threads_coder);
	free(values->thread_monitor);
	pthread_mutex_destroy(values->mut);
	free(values->mut);
	pthread_mutex_destroy(values->sched_mut);
	free(values->sched_mut);
	pthread_cond_destroy(values->sched_cond);
	free(values->sched_cond);
	return (0);
}
