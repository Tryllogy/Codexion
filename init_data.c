/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:38:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/22 14:06:53 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"

t_coders	*init_coders(t_coders *coders, t_values values)
{
	int	i;

	i = 0;
	while (i++ < values.number_of_coders)
		coders = add_back_coder(coders, new_coder(i));
	if (values.number_of_coders != 1)
		link_first_last_coders(coders);
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
