/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_simulation_started(t_philo *philo)
{
	t_data	*d;
	long	philos_ready;

	d = philo->data;
	if (DEBUG_MODE)
		printf("%ld\t%d thread created 🟡\n",
			get_timestamp_ms(d), philo->id);
	while (get_long(&d->start_time, &d->lock, d) == O_NOTINITYET)
		wait(1, d);
	if (DEBUG_MODE)
		printf("%ld\t%d started routine 🟢\n",
			get_timestamp_ms(d), philo->id);
	philos_ready = get_long(&d->philos_ready, &d->lock, d);
	set_long(&d->philos_ready, philos_ready + 1, &d->lock, d);
	if (DEBUG_MODE)
		printf("%ld\t%d philos ready: %ld 🟠\n",
			get_timestamp_ms(d), philo->id, philos_ready + 1);
}

void	wait_all_philos_ready(t_data *d)
{
	if (DEBUG_MODE)
		printf("%ld\tmonitoring thread created 🟤\n",
			get_timestamp_ms(d));
	while (get_long(&d->philos_ready, &d->lock, d) != d->philos_nb)
		wait(1, d);
	if (DEBUG_MODE)
		printf("%ld\tmonitoring started routine 🔵\n",
			get_timestamp_ms(d));
}

static bool	philo_finished_meals(t_philo *p)
{
	long		meals_done;

	meals_done = get_long(&p->meals_done, &p->lock, p->data);
	return (meals_done >= p->data->meals_per_philo);
}

/**
 * Optimize to avaoid recalculating
 */
bool	all_meals_done(t_data *d)
{
	int		philos_finished;
	int		i;

	if (d->meals_per_philo == O_NOMEALSLIMIT)
		return (false);
	philos_finished = 0;
	i = 0;
	while (i < d->philos_nb)
	{
		if (philo_finished_meals(&d->philos[i]))
			philos_finished++;
		i++;
	}
	return (philos_finished == d->philos_nb);
}

bool	philo_starved(t_philo *p)
{
	long	last_meal_time;
	long	since_last_meal;
	bool	ret;

	last_meal_time = get_long(&p->last_meal_time, &p->lock, p->data);
	if (last_meal_time < 0)
		return (false);
	since_last_meal = current_time_us(p->data) - last_meal_time;
	ret = false;
	if (since_last_meal > p->data->time_to_die)
	{
		ret = true;
		do_die(p);
	}
	return (ret);
}

bool	simulation_finished(t_data *data)
{
	return (get_bool(&data->stop_simulation, &data->lock, data));
}