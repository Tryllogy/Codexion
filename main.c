/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:40:01 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 15:19:36 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coders/coders.h"

void print_coders(t_coders *coders, int n_coders)
{
	int i;
	t_coders *tmp;

	tmp = coders;
	i = 0;
	while (i < n_coders)
	{
		printf("CODER[%d] : ID = %d DONGLE[0] = %d | DONGLE[1] = %d\n", tmp->id - 1,
			   tmp->id, tmp->dongles[0]->id, tmp->dongles[1]->id);
		i++;
		tmp = tmp->next;
	}
}

void print_threads(t_thread *threads, int n_threads)
{
	int i;

	i = 0;
	while (i < n_threads)
	{
		printf("THREAD %d : CODER %d | COMPILED %d | ALIVE %d\n", i,
			   threads[i].coder->id, threads[i].coder->n_compiled,
			   threads[i].coder->alive);
		i++;
	}
}

void print_values(t_values values)
{
	printf("NUMBER OF CODERS : %d\n", values.number_of_coders);
	printf("TIME TO BURNOUT : %lu\n", values.time_to_burnout);
	printf("TIME TO COMPILE : %lu\n", values.time_to_compile);
	printf("TIME TO DEBUG : %lu\n", values.time_to_debug);
	printf("TIME TO REFACTOR : %lu\n", values.time_to_refactor);
	printf("NUMBER OF COMPILES REQUIRED : %d\n", values.number_of_compiles_required);
	printf("DONGLE COOLDOWN : %lu\n", values.dongle_cooldown);
	printf("SCHEDULER : %s\n", values.scheduler);
}

void print_dongles(t_dongle *dongles, int n_dongles)
{
	int i;

	i = 0;
	while (i < n_dongles)
	{
		printf("DONGLE %d : ID = %d | AVAILABLE = %d\n", i, dongles[i].id, dongles[i].available);
		i++;
	}
}

int check_coders(t_values *values)
{
	int i;
	int n_thread;
	int time_to_compile;
	int finished;

	finished = 0;
	n_thread = values->number_of_coders;
	time_to_compile = values->number_of_compiles_required;
	i = 0;
	while (i < n_thread)
	{
		if (values->threads[i].coder->alive && values->threads[i].coder->n_compiled >= time_to_compile)
			finished++;
		else if (values->threads[i].coder->alive == 0)
			finished++;
		i++;
	}
	if (finished == n_thread)
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	t_values values;

	if (check_args(argc, argv))
		return (error_parsing());
	init_values(&values, argv);
	// print_values(values);
	// print_threads(values.threads, values.number_of_coders);
	// print_dongles(values.dongles, values.number_of_coders);
	// print_coders(values.coders, values.number_of_coders);
	if (check_malloc(&values))
		return (error(&values));
	gettimeofday(&values.start_time, NULL);
	create_threads(&values);
	while (!values.finished)
		values.finished = check_coders(&values);
	join_threads(&values);
	return (success(&values));
}
