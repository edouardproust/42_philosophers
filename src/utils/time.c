/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Sleep for `ms` milliseconds.
 */
void	wait(int ms)
{
	usleep(ms * 1000L);
}

/**
 * Get the current time in milliseconds.
 */
long	current_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000L + now.tv_usec / 1000);
}

/**
 * Get the interval in milliseconds since the program started.
 */
long	get_timestamp(t_data *d)
{
	long	now;

	now = current_time();
	return (now - d->start_time);
}
