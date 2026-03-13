/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:59:45 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/13 13:25:00 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

void	link_coder_dongle(t_coders *coder, t_values *values, int id)
{
	coder->dongles[1] = &values->dongles[id];
	if (id == 0)
		coder->dongles[0] = &values->dongles[values->number_of_coders - 1];
	else
		coder->dongles[0] = &values->dongles[id - 1];
}

void	link_dongle_coder(t_coders *coders, t_values *values, int id)
{
	values->dongles[id].coders[0] = &coders[id];
	if (id == values->number_of_coders - 1)
		values->dongles[id].coders[1] = &coders[0];
	else
		values->dongles[id].coders[1] = &coders[id + 1];
}
