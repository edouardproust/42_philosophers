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
# include <pthread.h> // pthread_* functions
# include <unistd.h> // write, usleep
# include <sys/time.h> // gettimeofday
# include <errno.h> // EAGAIN, EPERM, EINVAL,...
# include <limits.h> // INT_MAX
# include <stdbool.h> // bool, true, fals

/****************************************/
/* Defines & Enums                      */
/****************************************/

# define O_NOMEALSLIMIT -1
# define O_INITLATER -2

typedef enum e_mutexop
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
}	t_mutexop;

typedef enum e_threadop
{
	CREATE,
	JOIN,
	DETACH,
}	t_threadop;

typedef enum e_action
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_action;

/****************************************/
/* Structs                              */
/****************************************/

typedef struct s_data t_data;
typedef unsigned int t_bool;
typedef pthread_t t_thread;
typedef pthread_mutex_t t_mutex;

typedef struct s_fork
{
	int		index;
	t_mutex	lock;
}	t_fork;

typedef struct s_philo
{
	int			index;
	int			id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	long		last_meal_time;
	int			meals_done;
	t_data		*data;
	t_thread	thread;
	t_mutex		meal_lock;
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
	bool		death;
	t_mutex		death_lock;
	t_mutex		print_lock;
	t_thread	monitoring;
}	t_data;

/****************************************/
/* Functions                            */
/****************************************/

t_data	*init_data(char **args);

/* Routines */
void    *philosopher_routine(void *philo_ptr);
void    *monitoring_routine(void *data_ptr);

/* Actions */
void	do_eat(t_philo *philo);
void	do_sleep(t_philo *philo);
void	do_think(t_philo *philo);
void	do_die(t_philo *philo);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	put_action(int action_code, t_philo *philo);

/* Threads */
void	create_philo_thread(t_philo *philo);
void	thread_do(t_threadop op, pthread_t *thread, void *(*fn)(void *),
			t_data *d);
void	join_philo_threads(t_data *d);

/* Mutex */
void	mutex_do(t_mutexop op, t_mutex *mutex, t_data *d);
void	destroy_mutexes(t_data *d);

/* Time */
void	wait(int ms);
long	current_time(void);
long	get_timestamp(t_data *d);

/* Exit */
void	exit_program(char *error_msg, t_data **d);
void	exit_on_inval_arg(char *error_msg, char *wrong_arg, t_data **d);

/* Free */
void	*ft_free(void **ptr);
void	free_philos(t_philo **philos);
void	free_forks(t_fork **forks);
void	free_data(t_data **data);

/* Utils */
bool	is_even(int nb);
int		str_to_uint(char *str, t_data *d);

#endif
