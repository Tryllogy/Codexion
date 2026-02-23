/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 15:02:48 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/17 15:06:06 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./coders/coders.h"

int	error_parsing(void)
{
	printf("Error parsing arguments.\n");
	return (1);
}

int	error_no_args(void)
{
	printf("Error not enough arguments passed. (need 8)\n");
	return (1);
}
