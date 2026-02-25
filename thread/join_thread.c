/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 19:27:19 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 14:39:16 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	join_threads(pthread_t *thread_coder, int n_thread)
{
	int	i;

	i = 0;
	while (i < n_thread)
	{
		pthread_join(thread_coder[i], NULL);
		i++;
	}
}
