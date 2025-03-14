/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_action_str(t_philo *philo, char *str)
{
	printf("%ld %d %s\n", get_timestamp_ms(philo->data), philo->id, str);
}

void put_action(int action_code, t_philo *philo)
{
	mutex_do(LOCK, &philo->data->print_lock, philo->data);
	if (action_code == TAKE_FORK)
		put_action_str(philo, "has taken a fork");
	else if (action_code == EAT)
		put_action_str(philo, "is eating");
		else if (action_code == SLEEP)
		put_action_str(philo, "is sleeping");
	else if (action_code == THINK)
		put_action_str(philo, "is thinking");
	else if (action_code == DIE)
		put_action_str(philo, "died");
	else
		exit_program("put_action: wrong action_code", &philo->data);
	mutex_do(UNLOCK, &philo->data->print_lock, philo->data);
}

void	take_forks(t_philo *philo)
{
	mutex_do(LOCK, &philo->first_fork->lock, philo->data);
	put_action(TAKE_FORK, philo);
	mutex_do(LOCK, &philo->second_fork->lock, philo->data);
	put_action(TAKE_FORK, philo);
}

void	release_forks(t_philo *philo)
{
	mutex_do(UNLOCK, &philo->first_fork->lock, philo->data);
	mutex_do(UNLOCK, &philo->second_fork->lock, philo->data);
}
