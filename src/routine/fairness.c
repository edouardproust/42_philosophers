/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fairness.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
* Check if the given philosopher has the higest priority to eat.
*/
static bool	is_highest_priority_philo(t_philo *philo)
{
	long	highest_priority;
	long	priority;
	t_philo	*chosen;
	t_data	*d;
	int		i;

	highest_priority = -1;
	chosen = NULL;
	d = philo->data;
	i = 0;
	while (i < d->philos_nb)
	{
		priority = get_long(&d->philos[i].priority,
				&d->philos[i].priority_lock, d);
		if (priority > highest_priority)
		{
			highest_priority = priority;
			chosen = &d->philos[i];
		}
		i++;
	}
	return (chosen == philo);
}

void	wait_philo_turn(t_philo *philo)
{
	while (1)
	{
		if (simulation_finished(philo->data)
			|| is_highest_priority_philo(philo))
			break ;
		wait_action(10, philo);
	}
}

/**
 * Update priority of the given philosopher.
 *
 * This function is used by the monitor routine.
 * Priority is based on the time since last meal for the given philosopher.
 */
void	update_priority(t_philo *p)
{
	long	time_since_meal;

	time_since_meal = time_since_last_meal(p, US);
	set_long(&p->priority, time_since_meal, &p->priority_lock, p->data);
}
