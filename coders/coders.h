/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:37:27 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/01 14:53:27 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
#define CODERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

// STRUCTURES
typedef struct s_values
{
	int number_of_coders;
	__int64_t time_to_burnout;
	__int64_t time_to_compile;
	__int64_t time_to_debug;
	__int64_t time_to_refactor;
	int number_of_compiles_required;
	__int64_t dongle_cooldown;
	char *scheduler;
	int finished;
	struct s_dongle *dongles;
	struct s_coders *coders;
	struct s_thread *threads;
	pthread_t *threads_coder;
	pthread_t *thread_monitor;
	struct timeval start_time;
} t_values;

typedef struct s_dongle
{
	int id;
	int available;
	pthread_mutex_t *mutex;
} t_dongle;

typedef struct s_coders
{
	int id;
	int n_compiled;
	int alive;
	int last_compile_start;
	struct s_dongle *dongles[2];
	struct s_coders *next;
	struct s_coders *prev;
} t_coders;

typedef struct s_thread
{
	t_coders *coder;
	struct s_values *values;
	pthread_cond_t *cond;
} t_thread;

// INIT
void init_values(t_values *values, char **argv);
t_coders *init_coders(t_coders *coders, t_values values);
int check_args(int argc, char **argv);
t_thread *init_threads(t_thread *threads, t_values *values);
t_dongle *init_dongles(t_dongle *dongles, t_values values);

// UTILS
int ft_strlen(char *s);
void link_first_last_coders(t_coders *coders,
							t_dongle *dongles);
t_coders *add_back_coder(t_coders *coders, t_coders *new_coder);
t_coders *new_coder(int id, t_dongle *dongles, int n_coder);
__int64_t get_time_delta(struct timeval start_time);
int check_args(int argc, char **argv);

// FREE
int free_threads(t_thread *threads, pthread_t *thread_coder);
void free_coders(t_coders *coders, int n_coders);
int free_dongle(t_dongle *dongles, t_values values);

// ERRORS
int error_parsing(void);
int error_no_args(void);
int error(t_values *values);

// SUCCESS
int success(t_values *values);

// MUTEX
int lock_mutex(t_dongle *dongles[2]);
int unlock_mutex(t_dongle *dongles[2], t_values *values);

// THREAD
// CREATE
int create_threads(t_values *values);

// JOIN
void join_threads(t_values *values);

// COMPILE
void compile(t_thread *thread);

// DEBUG
void debug(t_thread *thread);

// REFACTOR
void refactor(t_thread *thread);

#endif