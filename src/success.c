/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:22:07 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 10:54:55 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int success(t_values *values)
{
	free_coders(values->coders, values->number_of_coders);
	free_mutex(values->dongles, *values);
	free(values->dongles);
	free(values->threads);
	free(values->threads_coder);
	free(values->thread_monitor);
	return (0);
}
