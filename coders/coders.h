/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:37:27 by tchemin           #+#    #+#             */
/*   Updated: 2026/03/07 18:37:49 by tchemin          ###   ########.fr       */
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
	pthread_mutex_t	*mut;
	pthread_mutex_t	*sched_mut;
	pthread_cond_t	*sched_cond;
}					t_values;

typedef struct s_dongle
{
	int				id;
	int				available;
	struct s_coders	*coders[2];
	__int64_t		next_available_time;
	pthread_mutex_t	*mutex;
	pthread_cond_t	*cond;
}					t_dongle;

typedef struct s_coders
{
	int				id;
	int				n_compiled;
	int				alive;
	int				waiting;
	__int64_t		last_compile_start_time;
	__int64_t		next_burnout_time;
	struct s_dongle	*dongles[2];
}					t_coders;

typedef struct s_thread
{
	t_coders		*coder;
	struct s_values	*values;
}					t_thread;

// INIT
int					init_values(t_values *values, char **argv);
t_coders			*init_coders(t_coders *coders, t_values values);
int					check_args(int argc, char **argv);
t_thread			*init_threads(t_thread *threads, t_values *values);
t_dongle			*init_dongles(t_dongle *dongles, t_values values);
void				init_ts(struct timespec *ts, t_dongle *dongle,
						__int64_t actual_time);
void				link_coder_dongle(t_coders *coder, t_values values, int id);
void				link_dongle_coder(t_coders *coders, t_values values,
						int id);

// UTILS
int					ft_strlen(char *s);
void				link_first_last_coders(t_coders *coders, t_dongle *dongles);
t_coders			*add_back_coder(t_coders *coders, t_coders *new_coder);
t_coders			*new_coder(int id, t_dongle *dongles, int n_coder);
__int64_t			get_time_delta(struct timeval start_time);
int					check_args(int argc, char **argv);

// FREE
int					free_threads(t_thread *threads, pthread_t *thread_coder);
void				free_coders(t_coders *coders);
void				*free_dongle(t_dongle *dongles, t_values *values,
						int n_dongles);

// ERRORS
int					error_parsing(void);
int					error_no_args(void);
int					error(t_values *values);

// SUCCESS
int					success(t_values *values);

// MUTEX
int					lock_mutex(t_thread *thread);
int					unlock_mutex(t_thread *thread);

// THREAD
// CREATE
int					create_threads(t_values *values);

// JOIN
void				join_threads(t_values *values);

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
t_coders			*set_coders(t_values *values);

// ROUTINE
int					routine(t_thread *thread);

// TAKE DONGLE
int					take_dongle(t_thread *thread);
int					put_dongle_down(t_thread *thread);

// EDF
t_coders			*edf(t_thread *thread);

#endif