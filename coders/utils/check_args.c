/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:18:45 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/13 13:25:26 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders.h"

int	contain_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		str++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
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
		if (n <= 0 && i == 1)
			return (1);
		else if (contain_digit(argv[i]) || (n < 0 && i > 1))
			return (1);
	}
	if (strcmp(argv[i], "edf") != 0 && strcmp(argv[i], "fifo") != 0)
		return (1);
	return (0);
}
