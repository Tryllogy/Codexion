/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:37:27 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/14 16:52:28 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// STRUCTURES
typedef struct s_values
{
	int				number_of_coders;
	int				number_of_compiles_required;
	int				finished;
	__int64_t		time_to_burnout;
	__int64_t		time_to_compile;
	__int64_t		time_to_debug;
	__int64_t		time_to_refactor;
	__int64_t		dongle_cooldown;
	int				id_next_coder;
	char			*scheduler;
	struct s_dongle	*dongles;
	struct s_coders	*coders;
	struct s_thread	*threads;
	struct timeval	start_time;
	pthread_t		*threads_coder;
	pthread_t		*thread_monitor;
	pthread_mutex_t	mut;
	pthread_mutex_t	sched_mut;
	pthread_cond_t	sched_cond;
	struct s_coders	**queue;
	int				n_in_queue;
}					t_values;

typedef struct s_dongle
{
	int				id;
	int				available;
	struct s_coders	*coders[2];
	__int64_t		next_available_time;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	pthread_t		owner;
	int				id_coder_promised;
	int				owner_set;
}					t_dongle;

typedef struct s_coders
{
	int				id;
	int				n_compiled;
	int				alive;
	int				waiting;
	__int64_t		last_compile_start_time;
	__int64_t		burnout;
	struct s_dongle	*dongles[2];
}					t_coders;

typedef struct s_thread
{
	t_coders		*coder;
	struct s_values	*values;
	pthread_t		this_thread;
	int				ready;
}					t_thread;

// INIT
// VALUES
int					init_values(t_values *values, char **argv);
pthread_t			*init_thread_values(int size);

// STRUCT
t_coders			*init_coders(t_coders *coders, t_values *values);
t_thread			*init_threads(t_thread *threads, t_values *values);
t_dongle			*init_dongles(t_dongle *dongles, t_values *values);
void				init_ts(struct timespec *ts, t_dongle *dongle,
						__int64_t actual_time);
void				link_coder_dongle(t_coders *coder, t_values *values,
						int id);
void				link_dongle_coder(t_coders *coders, t_values *values,
						int id);
int					init_queue(t_values *values);

// UTILS
int					check_args(int argc, char **argv);

// TIME
__int64_t			get_time_delta(struct timeval start_time);

// ARGS
int					check_args(int argc, char **argv);

// FREE
// FREE
int					free_threads(t_thread *threads, pthread_t *thread_coder);
void				free_coders(t_coders *coders);
void				*free_dongle(t_dongle *dongles, t_values *values,
						int n_dongles);

// RETURN MAIN
// ERRORS
int					error_parsing(void);
int					error(t_values *values);

// SUCCESS
int					success(t_values *values);

// THREAD
// CREATE
int					create_threads(t_values *values);

// JOIN
void				join_threads(t_values *values);

// ACTIONS
// COMPILE
void				compile(t_thread *thread);

// DEBUG
void				debug(t_thread *thread);

// REFACTOR
void				refactor(t_thread *thread);

// MONITOR
void				monitor_burnout(t_values *values);

// SETTER GETTER
int					set_finish(t_values *values);

// ROUTINE
int					routine(t_thread *thread);

// TAKE DONGLE
int					take_dongle(t_thread *thread);
int					put_dongle_down(t_thread *thread);

// WAIT TURN
void				wait_for_turn(t_thread *thread);
void				move_queue(t_coders **queue, int n_in_queue);
int					is_waiting(t_thread *thread);

// EDF
// EDF
t_coders			*edf(t_thread *thread);

#endif