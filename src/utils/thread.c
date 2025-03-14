/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_thread_error(int status, t_threadop op, t_data *d)
{
	if (status == EXIT_SUCCESS)
		return ;
	if (status == EAGAIN)
		exit_program("thread: not enough ressources", &d);
	else if (status == EPERM)
		exit_program("thread: no permission", &d);
	else if (status == EINVAL)
	{
		if (op == CREATE)
			exit_program("thread: create: invalid arg", &d);
		else if (op == JOIN || op == DETACH)
			exit_program("thread: thread not found", &d);
	}
	else if (status == ESRCH)
		exit_program("thread: thread not found", &d);
	else if (status == EDEADLK)
		exit_program("thread: deadlock or thread loop", &d);
}

void	create_philo_thread(t_philo *philo, void *(*routine_fn)(void *))
{
	int	status;

	status = pthread_create(&philo->thread, NULL, routine_fn, philo);
	handle_thread_error(status, CREATE, philo->data);
}

void	thread_do(t_threadop op, pthread_t *thread, void *(*fn)(void *),
	t_data *d)
{
	if (op == CREATE)
		handle_thread_error(pthread_create(thread, NULL, fn, d), op, d);
	else if (op == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), op, d);
	else if (op == DETACH)
		handle_thread_error(pthread_detach(*thread), op, d);
	else
		exit_program("thread_do: invalid op argument", &d);
}

void	join_philo_threads(t_data *d)
{
	int	status;
	int	i;

	i = 0;
	while (i < d->philos_nb)
	{
		status = pthread_join(d->philos[i].thread, NULL);
		handle_thread_error(status, JOIN, d);
		printf("%ld 🔵 philo %d: end 🏁\n", get_timestamp_ms(d), d->philos[i].id); //DEBUG
		i++;
	}
}
