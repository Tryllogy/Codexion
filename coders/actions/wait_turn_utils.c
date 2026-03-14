/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_turn_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 16:51:33 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/14 16:51:50 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

void	move_queue(t_coders **queue, int n_in_queue)
{
	int	i;

	i = 0;
	while (i < n_in_queue - 1)
	{
		queue[i] = queue[i + 1];
		i++;
	}
}

int	is_waiting(t_thread *thread)
{
	int			i;
	t_coders	**queue;
	t_coders	*coder;
	int			n_in_queue;

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
