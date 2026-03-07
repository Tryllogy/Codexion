/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/07 17:16:26 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	create_threads(t_values *values)
{
	int	i;

	if (!values->threads_coder || !values->threads)
		return (free_threads(values->threads, values->threads_coder));
	i = 0;
	while (i < values->number_of_coders)
	{
		if (pthread_create(&values->threads_coder[i], NULL, (void *)routine,
				&values->threads[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&*values->thread_monitor, NULL, (void *)monitor_burnout,
			values) != 0)
		return (1);
	return (0);
}
