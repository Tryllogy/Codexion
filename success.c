/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   success.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 18:22:07 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/21 18:24:17 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"

int	success(t_coders *coders, int n_coders)
{
	free_coders(coders, n_coders);
	return (0);
}
