/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Set the value of a long protected by a mutex.
 */
void	set_int(int *dest, int value, t_mutex *mutex, t_data *d)
{
	mutex_do(LOCK, mutex, d);
	*dest = value;
	mutex_do(UNLOCK, mutex, d);
}

/**
 * Set the value of a long protected by a mutex.
 */
void	set_long(long *dest, long value, t_mutex *mutex, t_data *d)
{
	mutex_do(LOCK, mutex, d);
	*dest = value;
	mutex_do(UNLOCK, mutex, d);
}

/**
 * Set the value of a bool protected by a mutex.
 */
void	set_bool(bool *dest, bool value, t_mutex *mutex, t_data *d)
{
	mutex_do(LOCK, mutex, d);
	*dest = value;
	mutex_do(UNLOCK, mutex, d);
}
