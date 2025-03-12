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
	A_DIED,
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
	pthread_mutex_t	lock;
}	t_fork;

typedef struct s_data t_data;

typedef struct s_philo
{
	int				index;
	int				id;
	t_action		action;
	t_fork			*right_fork;
	t_fork			*left_fork;
	long			last_meal_time;
	int				meals_done;
	pthread_t		thread;
	t_data			*data;
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
	long		start_time;
	t_bool		death;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	print_lock;
}	t_data;

/****************************************/
/* Functions                            */
/****************************************/

/* Init */
t_data	*init_data(char **args);
t_fork	*init_forks(t_data *d);
t_philo	*init_philos(t_data *d);

/* Routine */
void    *routine_handler(void *philo_ptr);
void	do_die(t_philo *philo);
int		do_eat(t_philo *philo);
void	do_sleep(t_philo *philo);
void	do_think(t_philo *philo);
void	put_action(t_philo *philo, char *action, int action_code);
int		take_forks(t_philo *philo);
void	release_forks(t_philo *philo);

/* Thread */
void	create_mutex(pthread_mutex_t *mutex, t_data *d);
void	destroy_mutexes(t_data *d);
void	create_thread(t_philo *philo);
void	join_threads(t_data *d);

/* Free */
void	*ft_free(void **ptr);
void	free_philos(t_philo **philos);
void	free_forks(t_fork **forks);
void	free_data(t_data **data);

/* Utils */
void	exit_philo(char *error_msg, t_data **d);
void	exit_on_inval_arg(char *error_msg, char *wrong_arg, t_data **d);
void	free_data(t_data **d);
t_bool	is_even(int nb);
int		str_to_uint(char *str, t_data *d);
void	wait(int ms);
long	current_time(void);
long	get_timestamp(t_data *d);

#endif
