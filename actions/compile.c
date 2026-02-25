/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 14:43:46 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 18:39:57 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

void	compile(t_thread *thread)
{
	// thread = (t_thread *) thread;
	int	i;
	int	time;
	int	boolean;

	i = 0;
	boolean = 1;
	time = thread->values->time_to_compile;
	while (boolean)
	{
		usleep(1000);
		i++;
		if (i == time)
			boolean = 0;
	}
}
