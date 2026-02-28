/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:46 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/28 21:49:40 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void compile(t_thread *thread)
{
	int time_compile;
	int actual_time;

	if (!thread->coder->alive)
		return;

	actual_time = get_time(thread->values->start_time);
	thread->coder->last_compile_start = actual_time;
	time_compile = thread->values->time_to_compile;
	printf("%d %d is compiling\n", actual_time, thread->coder->id);
	usleep(1000 * time_compile);
}
