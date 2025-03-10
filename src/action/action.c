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

void	do_die(t_philo *philo, t_data *d)
{
	philo->action = A_DIED;
	put_action(philo, "died", d);
}

int	do_eat(t_philo *philo, t_data *d)
{
	if (take_forks(philo) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	philo->action = A_EATING;
	philo->last_meal_time = get_timestamp(d);
	put_action(philo, "is eating", d);
	wait(d->eat_time);
	drop_forks(philo);
	return (EXIT_SUCCESS);
}

void	do_sleep(t_philo *philo, t_data *d)
{
	philo->action = A_SLEEPING;
	put_action(philo, "is sleeping", d);
	wait(d->sleep_time);
}

void	do_think(t_philo *philo, t_data *d)
{
	philo->action = A_THINKING;
	put_action(philo, "is thinking", d);
}
