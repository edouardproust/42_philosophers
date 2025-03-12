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

void	do_die(t_philo *philo)
{
	philo->action = A_DIED;
	put_action(philo, "died", A_DIED);
}

int	do_eat(t_philo *philo)
{
	if (take_forks(philo) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	philo->action = A_EATING;
	philo->last_meal_time = get_timestamp(philo->data);
	put_action(philo, "is eating", A_EATING);
	wait(philo->data->eat_time);
	release_forks(philo);
	philo->meals_done++;
	return (EXIT_SUCCESS);
}

void	do_sleep(t_philo *philo)
{
	philo->action = A_SLEEPING;
	put_action(philo, "is sleeping", A_SLEEPING);
	wait(philo->data->sleep_time);
}

void	do_think(t_philo *philo)
{
	philo->action = A_THINKING;
	put_action(philo, "is thinking", A_THINKING);
}
