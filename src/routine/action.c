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
	philo->last_meal_time = current_time_us(philo->data);
	put_action(EAT, philo);
	wait_us(philo->data->time_to_eat, philo->data);
	release_forks(philo);
	philo->meals_done++;
}

void	do_sleep(t_philo *philo)
{
	put_action(SLEEP, philo);
	wait_us(philo->data->time_to_sleep, philo->data);
}

void	do_think(t_philo *philo)
{
	put_action(THINK, philo);
}

void	do_die(t_philo *philo)
{
	put_action(DIE, philo);
}
