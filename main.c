/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:40:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 15:09:50 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"

void	print_coders(t_coders *coders, int n_coders)
{
	int			i;
	t_coders	*tmp;

	tmp = coders;
	i = 0;
	while (i < n_coders)
	{
		printf("CODER[%d] : DONGLE[0] = %d | DONGLE[1] = %d\n", tmp->id,
			tmp->dongles[0]->id, tmp->dongles[1]->id);
		i++;
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv)
{
	t_values		values;
	t_coders		*coders;
	t_dongle		*dongles;

	if (check_args(argc, argv))
		return (error_parsing());
	init_values(&values, argv);
	dongles = NULL;
	coders = NULL;
	dongles = init_dongles(dongles, values);
	coders = init_coders(coders, values, dongles);
	if (!coders || !dongles)
		return (error(dongles, coders, values.number_of_coders));
	print_coders(coders, values.number_of_coders);
	// create_threads(coders, &values);
	return (success(coders, dongles, values.number_of_coders));
}
