/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:22:07 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/06 17:18:14 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	success(t_values *values)
{
	free_coders(values->coders);
	free_dongle(values->dongles, values, values->number_of_coders);
	free_threads(values->threads, values->threads_coder);
	free(values->thread_monitor);
	free(values->mut);
	return (0);
}
