/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:13:14 by eproust           #+#    #+#             */
/*   Updated: 2025/03/08 14:13:16 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <string.h> // memset
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // pthread_* functions
# include <limits.h> // INT_MAX

/****************************************/
/* Defines & Enums                      */
/****************************************/

/* Options */
# define O_NOMEALSLIMIT -1

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

typedef enum e_action
{
	A_EATING,
	A_SLEEPING,
	A_THINKING,
}	t_action;

typedef enum e_forkstate
{
	F_FREE,
	F_TAKEN,
}	t_forkstate;

/****************************************/
/* Structs                              */
/****************************************/

typedef struct s_fork
{
	int				index;
	t_forkstate		state;
}	t_fork;

typedef struct s_philo
{
	int				index;
	int				number;
	t_action		action;
	t_fork			*left_fork;
	t_fork			*right_fork;
}	t_philo;

typedef struct s_data
{
	int			philos_nb;
	int			eat_time;
	int			sleep_time;
	int			starve_time;
	int			meals_per_philo;
	t_philo		*philos;
	t_fork		*forks;
	long		start_time_ms;
}	t_data;

/****************************************/
/* Functions                            */
/****************************************/

/* Init */
t_data	*init_data(char **args);

/* Utils */
void	exit_philo(char *error_msg, t_data **d);
void	exit_on_inval_arg(char *error_msg, char *wrong_arg, t_data **d);
void	*ft_free(void **ptr);
void	free_data(t_data **d);
int		str_to_uint(char *str, t_data *d);
long	get_current_time_ms(void);
long	get_timestamp_ms(t_data *d);

#endif
