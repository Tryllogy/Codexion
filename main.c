/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:40:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/22 14:06:13 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"

int	main(int argc, char **argv)
{
	t_values	values;
	t_coders	*coders;

	if (check_args(argc, argv))
		return (error_parsing());
	init_values(&values, argv);
	coders = NULL;
	coders = init_coders(coders, values);
	return (success(coders, values.number_of_coders));
}
