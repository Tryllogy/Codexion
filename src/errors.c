/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:02:48 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 15:55:34 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int error_parsing(void)
{
	printf("Error parsing arguments.\n");
	return (1);
}

int error_no_args(void)
{
	printf("Error not enough arguments passed. (need 8)\n");
	return (1);
}

int error(t_values *values)
{
	if (values->coders)
		free_coders(values->coders, values->number_of_coders);
	if (values->dongles)
		free_dongle(values->dongles, values, values->number_of_coders);
	if (values->threads)
		free_threads(values->threads, values->threads_coder);
	return (1);
}
