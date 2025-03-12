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

void put_action(t_philo *philo, char *action, int action_code)
{
	(void)action_code;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%ld %d %s\n", get_timestamp(philo->data), philo->id, action);
	pthread_mutex_unlock(&philo->data->print_lock);
}

static int	take_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->lock);
	if (fork->state == F_FREE)
	{
		fork->state = F_TAKEN;
		pthread_mutex_unlock(&fork->lock);
		return (EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&fork->lock);
	return (EXIT_FAILURE);
}

static void	release_fork(t_fork *fork)
{
	pthread_mutex_lock(&fork->lock);
	fork->state = F_FREE;
	pthread_mutex_unlock(&fork->lock);
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
		release_fork(fork1);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	release_forks(t_philo *philo)
{
	release_fork(philo->right_fork);
	release_fork(philo->left_fork);
}
