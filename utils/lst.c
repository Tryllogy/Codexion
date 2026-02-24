/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:51:32 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/24 18:25:49 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

t_coders	*new_coder(int id, t_dongle *dongles, int n_coder)
{
	t_coders	*coder;
	int			i;

	if (!dongles)
		return (NULL);
	coder = malloc(sizeof(t_coders));
	if (!coder)
		return (NULL);
	coder->id = id;
	i = 0;
	while (i <= id)
	{
		if (i < n_coder && i == dongles[i].id && i == id)
			coder->dongles[1] = dongles[i];
		if (i < n_coder && i == dongles[i].id && i == id - 1)
			coder->dongles[0] = dongles[i];
		i++;
	}
	coder->next = NULL;
	coder->prev = NULL;
	coder->n_compiled = 0;
	return (coder);
}

t_coders	*add_back_coder(t_coders *coders, t_coders *new_coder)
{
	t_coders	*tmp;

	if (!new_coder)
		return (coders);
	if (!coders)
	{
		coders = new_coder;
		return (coders);
	}
	tmp = coders;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_coder;
	new_coder->prev = tmp;
	return (coders);
}

void	link_first_last_coders(t_coders *coders, t_dongle *dongles)
{
	t_coders	*tmp;

	if (!coders)
		return ;
	tmp = coders;
	while (tmp->next)
		tmp = tmp->next;
	coders->dongles[0] = dongles[tmp->id - 1];
	tmp->dongles[1] = dongles[0];
	tmp->next = coders;
	coders->prev = tmp;
}

void	free_coders(t_coders *coders, int n_coders)
{
	int			i;
	t_coders	*tmp;

	if (!coders)
		return ;
	i = 0;
	while (i <= n_coders)
	{
		tmp = coders->next;
		if (coders)
			free(coders);
		coders = tmp;
		i++;
	}
}
