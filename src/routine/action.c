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
	philo->last_meal_time = get_timestamp(philo->data);
	put_action(EAT, philo);
	wait(philo->data->eat_time);
	release_forks(philo);
	philo->meals_done++;
}

void	do_sleep(t_philo *philo)
{
	put_action(SLEEP, philo);
	wait(philo->data->sleep_time);
}

void	do_think(t_philo *philo)
{
	put_action(THINK, philo);
}

void	do_die(t_philo *philo)
{
	put_action(DIE, philo);
}
