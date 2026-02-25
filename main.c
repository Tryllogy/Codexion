/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:40:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/25 18:38:52 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"

void	print_coders(t_coders *coders, int n_coders)
{
	int			i;
	t_coders	*tmp;

	tmp = coders;
	i = 0;
	while (i < n_coders)
	{
		printf("CODER[%d] : DONGLE[0] = %d | DONGLE[1] = %d\n", tmp->id,
			tmp->dongles[0]->id, tmp->dongles[1]->id);
		i++;
		tmp = tmp->next;
	}
}

int	check_coders(t_values *values)
{
	int	i;
	int	n_thread;
	int	time_to_compile;
	int	finished;

	finished = 0;
	n_thread = values->number_of_coders;
	time_to_compile = values->number_of_compiles_required;
	i = 0;
	while (i < n_thread)
	{
		if (values->threads[i].coder->alive
			&& values->threads[i].coder->n_compiled >= time_to_compile)
			finished++;
		else if (values->threads[i].coder->alive == 0)
			finished++;
		i++;
	}
	if (finished == n_thread)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_values		values;

	if (check_args(argc, argv))
		return (error_parsing());
	init_values(&values, argv);
	if (!values.coders || !values.dongles)
		return (error(&values));
	print_coders(values.coders, values.number_of_coders);
	create_threads(&values);
	while (!values.finished)
		values.finished = check_coders(&values);
	join_threads(&values);
	return (success(&values));
}
