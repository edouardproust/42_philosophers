/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	mutex_do(LOCK, &philo->first_fork->lock, philo->data);
	put_action(TAKE_FIRST_FORK, philo);
	mutex_do(LOCK, &philo->second_fork->lock, philo->data);
	put_action(TAKE_SECOND_FORK, philo);
}

void	release_forks(t_philo *philo)
{
	mutex_do(UNLOCK, &philo->first_fork->lock, philo->data);
	mutex_do(UNLOCK, &philo->second_fork->lock, philo->data);
}

void	increment_meals_count(t_philo *philo)
{
	long	meals_done;

	meals_done = get_int(&philo->meals_done, &philo->lock, philo->data);
	set_int(&philo->meals_done, meals_done + 1, &philo->lock, philo->data);
	if (DEBUG_MODE && (meals_done + 1 == philo->data->meals_per_philo))
	{
		printf("%ld\t%d finished meals ✅\n",
			get_timestamp_ms(philo->data), philo->id);
	}
}

long	time_since_last_meal(t_philo *philo, t_timeunit unit)
{
	t_data	*d;
	long	last_meal_time;
	long	result;

	d = philo->data;
	last_meal_time = get_long(&philo->last_meal_time, &philo->lock, d);
	result = current_time_us(d) - last_meal_time;
	if (unit == MS)
		return (result / 1000);
	return (result);
}
