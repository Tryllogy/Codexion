/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchemin <tchemin@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:37:27 by tchemin           #+#    #+#             */
/*   Updated: 2026/02/22 14:06:38 by tchemin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODERS_H
# define CODERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// STRUCTURES
typedef struct s_values
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	char			*scheduler;
}					t_values;

typedef struct s_coders
{
	int				id;
	int				n_compiled;
	struct s_coders	*next;
	struct s_coders	*prev;
}					t_coders;

// INIT
void				init_values(t_values *values, char **argv);
t_coders			*init_coders(t_coders *coders, t_values values);
int					check_args(int argc, char **argv);

// UTILS
int					ft_strlen(char *s);
void				link_first_last_coders(t_coders *coders);
t_coders			*add_back_coder(t_coders *coders, t_coders *new_coder);
t_coders			*new_coder(int id);
void				free_coders(t_coders *coders, int n_coders);

// ERRORS
int					error_parsing(void);
int					error_no_args(void);

// SUCCESS
int					success(t_coders *coders, int n_coders);

#endif