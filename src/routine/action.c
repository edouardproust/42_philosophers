/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_eat(t_philo *philo)
{
	take_forks(philo);
	increment_meals_count(philo);
	put_action(EAT, philo);
	set_long(&philo->last_meal_time, current_time_us(philo->data),
		&philo->lock, philo->data);
	wait_action(philo->data->time_to_eat, philo);
	release_forks(philo);
}

void	do_sleep(t_philo *philo)
{
	put_action(SLEEP, philo);
	wait_action(philo->data->time_to_sleep, philo);
}

void	do_think(t_philo *philo)
{
	put_action(THINK, philo);
}

void	do_die(t_philo *philo)
{
	put_action(DIE, philo);
}
