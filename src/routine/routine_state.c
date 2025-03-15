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

bool	all_philos_finished_meals(t_data *d)
{
	int		i;
	t_philo	*p;
	long	meals_done;

	if (d->meals_per_philo == O_NOMEALSLIMIT)
		return (false);
	i = 0;
	while (i < d->philos_nb)
	{
		p = &d->philos[i];
		meals_done = get_int(&p->meals_done, &p->lock, d);
		if (meals_done < d->meals_per_philo)
			return (false);
		i++;
	}
	return (true);
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
