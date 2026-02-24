/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:38:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/24 18:22:31 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

t_coders	*init_coders(t_coders *coders, t_values values, t_dongle *dongles)
{
	int	i;

	i = -1;
	while (i++ < values.number_of_coders)
		coders = add_back_coder(coders, new_coder(i, dongles,
					values.number_of_coders));
	link_first_last_coders(coders, dongles);
	return (coders);
}

void	init_values(t_values *values, char **argv)
{
	values->number_of_coders = atoi(argv[1]);
	values->time_to_burnout = atoi(argv[2]);
	values->time_to_compile = atoi(argv[3]);
	values->time_to_debug = atoi(argv[4]);
	values->time_to_refactor = atoi(argv[5]);
	values->number_of_compiles_required = atoi(argv[6]);
	values->dongle_cooldown = atoi(argv[7]);
	values->scheduler = argv[8];
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

void	init_thread(t_thread *thread, t_values values, int id)
{
	thread->id_coder = id;
	thread->time_to_compile = values.time_to_compile;
	thread->time_to_burnout = values.time_to_burnout;
	thread->scheduler = values.scheduler;
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
