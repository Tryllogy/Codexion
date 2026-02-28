/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refactor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:27 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/28 21:33:13 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void refactor(t_thread *thread)
{
    int actual_time;

    if (!thread->coder->alive)
        return;

    actual_time = get_time(thread->values->start_time);
    thread->coder->last_compile_start = actual_time;
    printf("%d %d is refactoring\n", actual_time, thread->coder->id);
}
