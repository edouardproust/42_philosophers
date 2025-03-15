/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philosopher_routine(void *philo_ptr)
{
	t_philo *philo;
	t_data 	*d;

	philo = (t_philo *)philo_ptr;
	wait_simulation_started(philo);
	d = philo->data;
	set_long(&philo->last_meal_time, current_time_us(d), &philo->lock, d);
	if (d->philos_nb == 1)
		put_action(TAKE_FIRST_FORK, philo);
	while(!simulation_finished(philo->data))
	{
		if (d->philos_nb > 1)
		{
			do_eat(philo);
			do_sleep(philo);
			do_think(philo);
		}
		wait(10, d);
	}
	return (NULL);
}

void    *monitoring_routine(void *data_ptr)
{
	t_data	*d;
	t_philo	*philo;
	int		i;

	d = (t_data *)data_ptr;
	wait_all_philos_ready(d);
	while (!simulation_finished(d))
	{
		i = 0;
		while (i < d->philos_nb)
		{
			philo = &d->philos[i];
			if (philo_finished_meals(philo) || philo_starved(philo))
			{
				set_bool(&d->stop_simulation, true, &d->lock, d);
				break ;
			}
			i++;
		}
		wait(10, d);
	}
	return (NULL);
}
