/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_data *d)
{
	if (status == EXIT_SUCCESS)
		return ;
	else if (status == EINVAL)
		exit_program("mutex: invalid mutex pointer", &d);
	else if (status == EDEADLK)
		exit_program("mutex: deadlock", &d);
	else if (status == EPERM)
		exit_program("mutex: current thread not allowed", &d);
	if (status == ENOMEM)
		exit_program("mutex: not enough memory", &d);
	else if (status == EBUSY)
		exit_program("mutex: locked", &d);
}

void	mutex_do(t_mutexop op, t_mutex *mutex, t_data *d)
{
	if (op == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), d);
	else if (op == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), d);
	else if (op == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), d);
	else if (op == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), d);
	else
		exit_program("mutex_do: invalid op argument", &d);
}

void	destroy_mutexes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philos_nb)
	{
		pthread_mutex_destroy(&(d->forks[i]).lock);
		pthread_mutex_destroy(&(d->philos[i]).lock);
		i++;
	}
	pthread_mutex_destroy(&d->lock);
	pthread_mutex_destroy(&d->print_lock);
}
