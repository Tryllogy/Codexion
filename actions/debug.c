/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:41 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/28 21:32:04 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void debug(t_thread *thread)
{
    int actual_time;

    if (!thread->coder->alive)
        return;

    actual_time = get_time(thread->values->start_time);
    thread->coder->last_compile_start = actual_time;
    printf("%d %d is debuging\n", actual_time, thread->coder->id);
}
