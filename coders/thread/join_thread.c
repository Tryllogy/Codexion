/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 19:27:19 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/12 15:39:42 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

void join_threads(t_values *values)
{
	int i;

	i = 0;
	while (i < values->number_of_coders)
	{
		pthread_join(values->threads_coder[i], NULL);
		i++;
	}
	pthread_join(*values->thread_monitor, NULL);
}
