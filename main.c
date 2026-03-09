/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:40:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/09 17:27:49 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"

void	print_coders(t_coders *coders, int n_coders)
{
	int	i;

	i = 0;
	while (i < n_coders)
	{
		printf("CODER[%d] : ID = %d DONGLE[0] = %d | DONGLE[1] = %d\n",
			coders[i].id - 1, coders[i].id, coders[i].dongles[0]->id,
			coders[i].dongles[1]->id);
		i++;
	}
	printf("\n");
}

void	print_threads(t_thread *threads, int n_threads)
{
	int	i;

	i = 0;
	while (i < n_threads)
	{
		printf("THREAD %d : CODER %d | COMPILED %d | ALIVE %d\n", i,
			threads[i].coder->id, threads[i].coder->n_compiled,
			threads[i].coder->alive);
		i++;
	}
	printf("\n");
}

void	print_values(t_values values)
{
	printf("NUMBER OF CODERS : %d\n", values.number_of_coders);
	printf("TIME TO BURNOUT : %lu\n", values.time_to_burnout);
	printf("TIME TO COMPILE : %lu\n", values.time_to_compile);
	printf("TIME TO DEBUG : %lu\n", values.time_to_debug);
	printf("TIME TO REFACTOR : %lu\n", values.time_to_refactor);
	printf("NUMBER OF COMPILES REQUIRED : %d\n",
		values.number_of_compiles_required);
	printf("DONGLE COOLDOWN : %lu\n", values.dongle_cooldown);
	printf("SCHEDULER : %s\n", values.scheduler);
	printf("\n");
}

void	print_dongles(t_dongle *dongles, int n_dongles)
{
	int	i;

	i = 0;
	while (i < n_dongles)
	{
		printf("DONGLE %d : ID = %d CODER[0] = %d | CODER[1] = %d\n", i,
			dongles[i].id, dongles[i].coders[0]->id - 1,
			dongles[i].coders[1]->id - 1);
		i++;
	}
	printf("\n");
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
	// print_values(values);
	// print_dongles(values.dongles, values.number_of_coders);
	// print_coders(values.coders, values.number_of_coders);
	// print_threads(values.threads, values.number_of_coders);
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
