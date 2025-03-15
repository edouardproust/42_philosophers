/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_philo_thread_debug(t_philo *p, t_debugop op)
{
	if (!DEBUG_MODE)
		return ;
	mutex_do(LOCK, &p->data->print_lock, p->data);
	if (op == PHILO_CREATED)
		printf("%ld\t%d thread created 🟡\n",
			get_timestamp_ms(p->data), p->id);
	else if (op == PHILO_STARTED)
		printf("%ld\t%d started routine 🟢\n",
			get_timestamp_ms(p->data), p->id);
	mutex_do(UNLOCK, &p->data->print_lock, p->data);
}

void	wait_simulation_started(t_philo *philo)
{
	t_data	*d;

	d = philo->data;
	put_philo_thread_debug(philo, PHILO_CREATED);
	while (get_long(&d->start_time, &d->lock, d) == O_NOTINITYET)
		wait(1, d);
	put_philo_thread_debug(philo, PHILO_STARTED);
}
