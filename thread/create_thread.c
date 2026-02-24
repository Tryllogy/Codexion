/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:41:43 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/24 19:26:31 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	routine(t_thread *thread)
{
	int	n_times;

	printf("routine\n");
	if (!thread)
		return (1);
	n_times = thread->values.number_of_compiles_required;
	while (thread->coder->n_compiled <= n_times)
	{
		(thread->coder->n_compiled)++;
	}
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

int	free_threads(t_thread *threads, pthread_t *thread_coder, int n_coder)
{
	int	i;

	i = 0;
	while (i < n_coder)
	{
		if (&threads[i])
			free(&threads[i]);
		if (&thread_coder[i])
			free(&thread_coder[i]);
		i++;
	}
	return (1);
}

int	create_thread(t_coders *coders, t_values values)
{
	int			i;
	pthread_t	*thread_coder;
	t_thread	*threads;

	threads = NULL;
	thread_coder = NULL;
	threads = init_threads(coders, threads, values);
	if (!threads)
		return (free_threads(threads, thread_coder, values.number_of_coders));
	thread_coder = malloc(sizeof(pthread_t) * values.number_of_coders);
	if (!thread_coder)
		return (free_threads(threads, thread_coder, values.number_of_coders));
	i = 0;
	while (i < values.number_of_coders)
	{
		if (pthread_create(&thread_coder[i], NULL, (void *)routine,
				&threads[i]) != 0)
			return (1);
		i++;
	}
	// usleep(5000);
	// free_threads(threads, thread_coder, values.number_of_coders);
	// join_threads(thread_coder, values.number_of_coders);
	return (0);
}
