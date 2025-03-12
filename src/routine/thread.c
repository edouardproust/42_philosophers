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

void	create_mutex(pthread_mutex_t *mutex, t_data *d)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
		exit_philo("pthread_mutex_init", &d);
}

void	destroy_mutexes(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philos_nb)
	{
		pthread_mutex_destroy(&(d->forks[i]).lock);
		i++;
	}
	pthread_mutex_destroy(&d->death_lock);
	pthread_mutex_destroy(&d->print_lock);
}

void	create_thread(t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, routine_handler, (void *)philo) != 0)
		exit_philo("pthread_create", &philo->data);
}

void	join_threads(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philos_nb)
	{
		pthread_join(d->philos[i].thread, NULL);
		i++;
	}
}