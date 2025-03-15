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
# include <limits.h> // INT_MAX, LONG_MAX
# include <stdbool.h> // bool, true, fals

/****************************************/
/* Defines & Enums                     */
/****************************************/

# define DEBUG_MODE 0
# define O_NOTINITYET -1
# define O_NOMEALSLIMIT -1
# define FOO 1337

# define BLUE "\033[1m\033[34m"
# define RED "\033[1m\033[31m"
# define RST "\033[0m" // Reset

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
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE,
}	t_action;

typedef enum e_timeunit
{
	MS,
	US,
}	t_timeunit;

typedef enum e_debugop
{
	PHILO_CREATED,
	PHILO_STARTED,
	MONIT_CREATED,
	MONIT_STARTED,
}	t_debugop;

/****************************************/
/* Structs                              */
/****************************************/

typedef struct s_data	t_data;
typedef unsigned int	t_bool;
typedef pthread_t		t_thread;
typedef pthread_mutex_t	t_mutex;

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
	long		priority;
	t_data		*data;
	t_thread	thread;
	t_mutex		priority_lock;
	t_mutex		lock;
}	t_philo;

typedef struct s_data
{
	int			philos_nb;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			meals_per_philo;
	t_philo		*philos;
	t_fork		*forks;
	long		start_time;
	bool		stop_simulation;
	t_mutex		lock;
	t_mutex		print_lock;
	t_thread	monitoring;
}	t_data;

/****************************************/
/* Functions                            */
/****************************************/

t_data	*init_data(char **args);

/* Routines */
void	*philosopher_routine(void *philo_ptr);
void	*monitoring_routine(void *data_ptr);
void	wait_simulation_started(t_philo *philo);
bool	philo_starved(t_philo *philo);
bool	all_philos_finished_meals(t_data *d);
bool	simulation_finished(t_data *data);

/* Actions */
void	do_eat(t_philo *philo);
void	do_sleep(t_philo *philo);
void	do_think(t_philo *philo);
void	do_die(t_philo *philo);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	put_action(int action_code, t_philo *philo);
void	wait_action(long time, t_philo *philo);
void	increment_meals_count(t_philo *philo);
long	time_since_last_meal(t_philo *philo, t_timeunit unit);

/* Fairness */
void	wait_philo_turn(t_philo *philo);
void	update_priority(t_philo *p);

/* Threads */
void	create_philo_thread(t_philo *philo, void *(*routine_fn)(void *));
void	thread_do(t_threadop op, pthread_t *thread, void *(*fn)(void *),
			t_data *d);
void	join_threads(t_data *d);

/* Mutex */
void	mutex_do(t_mutexop op, t_mutex *mutex, t_data *d);
void	destroy_mutexes(t_data *d);

/* Time */
void	wait(long time_us, t_data *d);
long	current_time_us(t_data *d);
long	get_timestamp_ms(t_data *d);

/* Exit */
void	exit_program(char *error_msg, t_data **d);
void	exit_program_init(char *error_msg, t_data **d);
void	exit_on_inval_arg(char *error_msg, char *wrong_arg, t_data **d);

/* Free */
void	*ft_free(void **ptr);
void	free_philos(t_philo **philos);
void	free_forks(t_fork **forks);
void	free_data(t_data **data);

/* Getters & setters */
int		get_int(int *value, t_mutex *mutex, t_data *d);
long	get_long(long *value, t_mutex *mutex, t_data *d);
bool	get_bool(bool *value, t_mutex *mutex, t_data *d);
void	set_int(int *dest, int value, t_mutex *mutex, t_data *d);
void	set_long(long *dest, long value, t_mutex *mutex, t_data *d);
void	set_bool(bool *dest, bool value, t_mutex *mutex, t_data *d);

/* Utils */
bool	is_even(int nb);
int		str_to_uint(char *str, t_data *d);

#endif
