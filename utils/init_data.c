/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:38:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 18:20:20 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

t_coders	*init_coders(t_coders *coders, t_values values)
{
	int	i;

	i = -1;
	while (i++ < values.number_of_coders)
		coders = add_back_coder(coders, new_coder(i, values.dongles,
					values.number_of_coders));
	link_first_last_coders(coders, values.dongles);
	return (coders);
}

void	init_values(t_values *values, char **argv)
{
	values->number_of_coders = atoi(argv[1]);
	values->time_to_burnout = atoi(argv[2]) * 1000;
	values->time_to_compile = atoi(argv[3]) * 1000;
	values->time_to_debug = atoi(argv[4]) * 1000;
	values->time_to_refactor = atoi(argv[5]) * 1000;
	values->number_of_compiles_required = atoi(argv[6]);
	values->dongle_cooldown = atoi(argv[7]) * 1000;
	values->scheduler = argv[8];
	values->finished = 0;
	values->dongles = NULL;
	values->coders = NULL;
	values->dongles = init_dongles(values->dongles, *values);
	values->coders = init_coders(values->coders, *values);
	values->threads = NULL;
	values->threads_coder = NULL;
	values->threads = init_threads(values->threads, *values);
	values->threads_coder = malloc(sizeof(pthread_t)
			* values->number_of_coders);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	n;

	if (argc != 9)
		return (1);
	i = 0;
	while (++i < 8)
	{
		n = atoi(argv[i]);
		if (n <= 0)
			return (1);
	}
	if (strcmp(argv[i], "edf") != 0 && strcmp(argv[i], "fifo") != 0)
		return (1);
	return (0);
}

t_thread	*init_threads(t_thread *threads, t_values values)
{
	int			i;
	t_coders	*tmp;

	threads = malloc(sizeof(t_thread) * values.number_of_coders);
	if (!threads)
		return (NULL);
	i = 0;
	tmp = values.coders;
	while (i < values.number_of_coders)
	{
		(&threads[i])->coder = tmp;
		(&threads[i])->values = &values;
		i++;
		tmp = tmp->next;
	}
	return (threads);
}

t_dongle	*init_dongles(t_dongle *dongles, t_values values)
{
	int	i;

	dongles = malloc(sizeof(t_dongle) * values.number_of_coders);
	if (!dongles)
		return (NULL);
	i = 0;
	while (i < values.number_of_coders)
	{
		dongles[i].id = i;
		pthread_mutex_init(&dongles[i].mutex, NULL);
		i++;
	}
	return (dongles);
}
