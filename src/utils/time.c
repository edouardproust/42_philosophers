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
 * Sleep for `time` micro-seconds.
 */
void	wait_us(long time, t_data *d)
{
	long	start;
	long	now;

	start = current_time_us(d);
	now = start;
	while (now - start < time)
	{
		if (time - now + start > 2000)
			usleep(time / 2);
		else
			usleep(1);
		now = current_time_us(d);
	}
}

/**
 * Get the current time in micro-seconds (us).
 */
long	current_time_us(t_data *d)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) != 0)
		exit_program("Error: current_time: gettimeofday failed\n", &d);
	return (now.tv_sec * 1000000L + now.tv_usec);
}

/**
 * Get the interval in milliseconds since the program started.
 */
long	get_timestamp_ms(t_data *d)
{
	long	now;
	long	simul_start;

	now = current_time_us(d);
	simul_start = get_long(&d->start_time, &d->lock, d);
	if (simul_start == O_NOTINITYET)
		return (O_NOTINITYET);
	return ((now - simul_start) / 1000);
}
