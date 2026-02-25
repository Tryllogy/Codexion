/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 19:27:19 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 18:38:31 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	join_threads(t_values *values)
{
	int	i;

	i = 0;
	while (i < values->number_of_coders)
	{
		pthread_join(values->threads_coder[i], NULL);
		i++;
	}
}
