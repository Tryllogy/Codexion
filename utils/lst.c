/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 17:51:32 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/21 18:35:47 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coders/coders.h"

t_coders	*new_coder(int id)
{
	t_coders	*coder;

	coder = malloc(sizeof(t_coders));
	if (!coder)
		return (NULL);
	coder->id = id;
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

void	link_first_last_coders(t_coders *coders)
{
	t_coders	*tmp;

	if (!coders)
		return ;
	tmp = coders;
	while (tmp->next)
		tmp = tmp->next;
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
	while (i++ < n_coders)
	{
		tmp = coders->next;
		if (coders)
			free(coders);
		coders = tmp;
	}
}
