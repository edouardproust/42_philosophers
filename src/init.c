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

static t_fork	*init_forks(int n)
{
	t_fork	*forks;
	int		i;

	forks = malloc(sizeof(t_fork) * n);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < n)
	{
		forks[i].index = i;
		forks[i].state = F_FREE;
		i++;
	}
	return (forks);
}

static t_philo	*init_philos(int n, t_fork *forks)
{
	t_philo	*philos;
	int		i;
	int		prev_fork_index;

	philos = malloc(sizeof(t_philo) * n);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < n)
	{
		philos[i].index = i;
		philos[i].number = i + 1;
		philos[i].action = A_THINKING;
		philos[i].left_fork = &forks[i];
		prev_fork_index = i - 1;
		if (prev_fork_index < 0)
			prev_fork_index = n - 1;
		philos[i].right_fork = &forks[prev_fork_index];
		i++;
	}
	return (philos);
}

t_data	*init_data(char **args)
{
	t_data *d;

	d = malloc(sizeof(t_data));
	d->start_time_ms = get_current_time_ms();
	d->forks = NULL;
	d->philos = NULL;
	d->philos_nb = str_to_uint(args[1], d);
	d->eat_time = str_to_uint(args[2], d);
	d->sleep_time = str_to_uint(args[3], d);
	d->starve_time = str_to_uint(args[4], d);
	d->meals_per_philo = O_NOMEALSLIMIT;
	if (args[5])
		d->meals_per_philo = str_to_uint(args[5], d);
	d->forks = init_forks(d->philos_nb);
	d->philos = init_philos(d->philos_nb, d->forks);
	return (d);
}