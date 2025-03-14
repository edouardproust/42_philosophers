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

static	void assign_forks_to_philo(t_fork *forks, t_philo *philo)
{
	t_fork	*left_fork;
	t_fork	*right_fork;

	if (philo->index == philo->data->philos_nb - 1)
	{
		left_fork = &forks[0];
		right_fork = &forks[philo->data->philos_nb - 1];
	}
	else
	{
		left_fork = &forks[philo->index];
		right_fork = &forks[philo->index + 1];
	}
	if (is_even(philo->index))
	{
		philo->first_fork = left_fork;
		philo->second_fork = right_fork;
	}
	else
	{
		philo->first_fork = right_fork;
		philo->second_fork = left_fork;
	}
}

t_fork	*init_forks(t_data *d)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * d->philos_nb);
	if (!forks)
		exit_program("malloc", &d);
	i = 0;
	while (i < d->philos_nb)
	{
		forks[i].index = i;
		mutex_do(INIT, &forks[i].lock, d);
		i++;
	}
	return (forks);
}

t_philo	*init_philos(t_data *d)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * d->philos_nb);
	if (!philos)
		exit_program("malloc", &d);
	i = 0;
	while (i < d->philos_nb)
	{
		mutex_do(INIT, &philos[i].lock, d);
		philos[i].index = i;
		philos[i].id = i + 1;
		set_long(&philos[i].last_meal_time, O_NOTINITYET , &philos[i].lock, d);
		philos[i].meals_done = 0;
		philos[i].data = d;
		assign_forks_to_philo(d->forks, &philos[i]);
		i++;
	}
	return (philos);
}

t_data	*init_data(char **args)
{
	t_data	*d;

	d = malloc(sizeof(t_data));
	if (!d)
		exit_program_init("malloc", &d);
	mutex_do(INIT, &d->lock, d);
	mutex_do(INIT, &d->print_lock, d);
	d->philos_nb = str_to_uint(args[1], d);
	d->time_to_die = str_to_uint(args[4], d) * 1000;
	d->time_to_eat = str_to_uint(args[2], d) * 1000;
	d->time_to_sleep = str_to_uint(args[3], d) * 1000;
	d->meals_per_philo = O_NOMEALSLIMIT;
	if (args[5])
		d->meals_per_philo = str_to_uint(args[5], d);
	set_long(&d->philos_ready, 0, &d->lock, d);
	set_long(&d->start_time, O_NOTINITYET, &d->lock, d);
	d->forks = init_forks(d);
	d->philos = init_philos(d);
	return (d);
}
