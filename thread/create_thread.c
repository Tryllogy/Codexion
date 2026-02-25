/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 14:52:19 by tchemin          ###   ########.fr       */
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

int	check_coders(t_thread *thread)
{
	int	i;
	int	n_thread;
	int	time_to_compile;
	int	finished;

	finished = 0;
	n_thread = (&thread[0])->values->number_of_coders;
	time_to_compile = (&thread[0])->values->number_of_compiles_required;
	i = 0;
	while (i < n_thread)
	{
		if ((&thread[i])->coder->alive
			&& (&thread[i])->coder->n_compiled >= time_to_compile)
			finished++;
		else if ((&thread[i])->coder->alive == 0)
			finished++;
		i++;
	}
	if (finished == n_thread)
		return (1);
	return (0);
}

int	create_threads(t_coders *coders, t_values *values)
{
	int			i;
	pthread_t	*thread_coder;
	t_thread	*threads;

	threads = NULL;
	thread_coder = NULL;
	threads = init_threads(coders, threads, *values);
	thread_coder = malloc(sizeof(pthread_t) * values->number_of_coders);
	if (!thread_coder || !threads)
		return (free_threads(threads, thread_coder));
	i = -1;
	while (i++ < values->number_of_coders - 1)
	{
		if (pthread_create(&thread_coder[i], NULL, (void *)routine,
				&threads[i]) != 0)
			return (1);
	}
	while (!values->finished)
	{
		usleep(100000);
		values->finished = check_coders(threads);
	}
	join_threads(thread_coder, values->number_of_coders);
	free_threads(threads, thread_coder);
	return (0);
}
