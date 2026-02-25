/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 18:35:17 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	routine(t_thread *thread)
{
	int	n_times;

	if (!thread)
		return (1);
	n_times = thread->values->number_of_compiles_required;
	while (thread->coder->n_compiled <= n_times)
	{
		compile(thread);
		// debug();
		// refactor();
		if (thread->coder->alive)
			(thread->coder->n_compiled)++;
	}
	return (0);
}
/*
	//TODO gere le temps avec le timestamp
	//TODO affcichage
	//bungee == fourchette --> partage le meme emplacement memoir
*/

int	free_threads(t_thread *threads, pthread_t *thread_coder)
{
	if (threads)
		free(threads);
	if (thread_coder)
		free(thread_coder);
	return (1);
}

int	create_threads(t_values *values)
{
	int	i;
	int	finished;

	if (!values->threads_coder || !values->threads)
		return (free_threads(values->threads, values->threads_coder));
	i = 0;
	finished = 0;
	while (i < values->number_of_coders)
	{
		if (pthread_create(&values->threads_coder[i], NULL, (void *)routine,
				&values->threads[i]) != 0)
			return (1);
		i++;
	}
	finished++;
	if (finished == values->number_of_coders)
		values->finished = 1;
	return (0);
}
