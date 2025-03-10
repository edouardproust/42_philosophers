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

void put_action(t_philo *philo, char *action, t_data *d)
{
	printf("%ld %d %s\n", get_timestamp(d), philo->id, action);
}

static int	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	if (fork->state == F_FREE)
	{
		fork->state = F_TAKEN;
		pthread_mutex_unlock(&fork->mutex);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&fork->mutex);
	return (EXIT_FAILURE);
}

static void	drop_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->state = F_FREE;
	pthread_mutex_unlock(&fork->mutex);
}

int	take_forks(t_philo *philo)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = philo->right_fork;
	fork2 = philo->left_fork;
	if (is_even(philo->index))
	{
		fork1 = philo->left_fork;
		fork2 = philo->right_fork;
	}
	if (take_fork(fork1) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (take_fork(fork2) != EXIT_SUCCESS)
	{
		drop_fork(fork1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	drop_forks(t_philo *philo)
{
	drop_fork(philo->right_fork);
	drop_fork(philo->left_fork);
}
