/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:26:48 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/13 13:25:18 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

int	set_finish(t_values *values)
{
	int	is_finished;

	pthread_mutex_lock(&values->mut);
	is_finished = values->finished;
	pthread_mutex_unlock(&values->mut);
	return (is_finished);
}

t_coders	*set_coders(t_values *values)
{
	t_coders	*coders;

	pthread_mutex_lock(&values->mut);
	coders = values->coders;
	pthread_mutex_unlock(&values->mut);
	return (coders);
}
