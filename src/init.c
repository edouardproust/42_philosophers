/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_fork	*init_forks(t_data *d)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * d->philos_nb);
	if (!forks)
		exit_philo("malloc", &d);
	i = 0;
	while (i < d->philos_nb)
	{
		forks[i].index = i;
		forks[i].state = F_FREE;
		create_mutex(&forks[i].lock, d);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_data *d)
{
	t_philo	*philos;
	int		i;
	int		prev_fork_index;

	philos = malloc(sizeof(t_philo) * d->philos_nb);
	if (!philos)
		exit_philo("malloc", &d);
	i = 0;
	while (i < d->philos_nb)
	{
		philos[i].index = i;
		philos[i].id = i + 1;
		philos[i].action = A_THINKING;
		philos[i].left_fork = &d->forks[i];
		prev_fork_index = i - 1;
		if (prev_fork_index < 0)
			prev_fork_index = d->philos_nb - 1;
		philos[i].right_fork = &d->forks[prev_fork_index];
		philos[i].last_meal_time = current_time();
		philos[i].meals_done = 0;
		create_thread(&philos[i]);
		i++;
	}
	return (philos);
}

t_data	*init_data(char **args)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		exit_philo("malloc", &d);
	d->start_time = current_time();
	d->forks = NULL;
	d->philos = NULL;
	d->philos_nb = str_to_uint(args[1], d);
	d->eat_time = str_to_uint(args[2], d);
	d->sleep_time = str_to_uint(args[3], d);
	d->starve_time = str_to_uint(args[4], d);
	d->meals_per_philo = O_NOMEALSLIMIT;
	if (args[5])
		d->meals_per_philo = str_to_uint(args[5], d);
	create_mutex(&d->death_lock, d);
	create_mutex(&d->print_lock, d);
	return (d);
}
