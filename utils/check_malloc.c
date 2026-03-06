/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_malloc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:18:40 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/06 17:18:41 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

int	check_malloc(t_values *values)
{
	if (!values->dongles || !values->coders || !values->threads
		|| !values->threads_coder || !values->thread_monitor)
		return (1);
	return (0);
}
