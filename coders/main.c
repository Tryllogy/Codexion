/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:40:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/14 16:54:35 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders.h"

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
		pthread_mutex_lock(&values->mut);
		if (values->threads[i].coder->alive
			&& values->threads[i].coder->n_compiled >= time_to_compile)
			finished++;
		else if (values->threads[i].coder->alive == 0)
			finished++;
		pthread_mutex_unlock(&values->mut);
		i++;
	}
	if (finished == n_thread)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_values	values;
	int			tmp;

	if (check_args(argc, argv))
		return (error_parsing());
	if (init_values(&values, argv))
		return (error(&values));
	if (strcmp(values.scheduler, "edf") == 0)
		if (init_queue(&values))
			return (error(&values));
	gettimeofday(&values.start_time, NULL);
	create_threads(&values);
	while (!set_finish(&values))
	{
		tmp = check_coders(&values);
		pthread_mutex_lock(&values.mut);
		values.finished = tmp;
		pthread_mutex_unlock(&values.mut);
	}
	join_threads(&values);
	return (success(&values));
}
