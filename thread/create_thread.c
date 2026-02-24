/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/24 16:42:09 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	init_thread_coder(pthread_t *thread_coder, t_thread *thread, int n_coder)
{
	thread_coder = malloc(sizeof(pthread_t) * n_coder);
	if (!thread_coder)
		return (1);
	thread = malloc(sizeof(t_thread) * n_coder);
	if (!thread)
		return (1);
	return (0);
}

int	compile(t_thread *thread)
{
	if (!thread)
		return (1);
	return (0);
}

/*
routine() fifo // edf
{
	compile()
	debug()
	refactor()
}
	//TODO gere le temps avec le timestamp
	//TODO affcichage
	//bungee == fourchette --> partage le meme emplacement memoir
*/

int	create_thread(t_coders *coders, t_values values)
{
	t_coders	*tmp;
	int			i;
	pthread_t	*thread_coder;
	t_thread	*thread;

	thread = NULL;
	thread_coder = NULL;
	if (!init_thread_coder(thread_coder, thread, values.number_of_coders))
		return (1);
	i = 0;
	tmp = coders;
	while (i < values.number_of_coders)
	{
		init_thread(&thread[i], values, tmp->id);
		if (pthread_create(&thread_coder[i], NULL, (void *)compile,
				&thread[i]) != 0)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
