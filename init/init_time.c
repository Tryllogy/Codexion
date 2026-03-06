/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 13:56:33 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/06 19:21:48 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	init_ts(struct timespec *ts, t_dongle *dongle, __int64_t actual_time)
{
	struct timeval	tv;
	__int64_t		remaining_ms;

	remaining_ms = dongle->next_available_time - actual_time;
	if (remaining_ms < 0)
		remaining_ms = 0;
	gettimeofday(&tv, NULL);
	ts->tv_sec = tv.tv_sec + (remaining_ms / 1000);
	ts->tv_nsec = (tv.tv_usec * 1000) + (remaining_ms % 1000) * 1000000;
	if (ts->tv_nsec >= 1000000000)
	{
		ts->tv_sec += ts->tv_nsec / 1000000000;
		ts->tv_nsec = ts->tv_nsec % 1000000000;
	}
}
