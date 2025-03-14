/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_simulation_started(t_philo *philo)
{
	t_data	*d;
	long	philos_ready;

	d = philo->data;
	printf("%ld 🔵 philo %d: thread created (wait) ⌛\n", get_timestamp_ms(d), philo->id); //DEBUG
	while (get_long(&d->start_time, &d->lock, d) == O_NOTINITYET)
		wait_us(1, d);
	printf("%ld 🔵 philo %d: started routine 🏳️\n", get_timestamp_ms(d), philo->id); //DEBUG
	philos_ready = get_long(&d->philos_ready, &d->lock, d);
	set_long(&d->philos_ready, philos_ready + 1, &d->lock, d);
	printf("%ld 🔵 philo %d: philos ready:%ld\n", get_timestamp_ms(d), philo->id, philos_ready + 1); //DEBUG
}

void    *philosopher_routine(void *philo_ptr)
{
	t_philo *philo;
	t_data 	*d;

	philo = (t_philo *)philo_ptr;
	wait_simulation_started(philo);
	d = philo->data;
	set_long(&philo->last_meal_time, current_time_us(d), &philo->lock, d);
	wait_us(philo->id * 1000000, d);//DEBUG
	return (NULL);
}

static void	wait_all_philos_ready(t_data *d)
{
	printf("%ld 🔵 monitoring: thread created (wait) ⌛\n", get_timestamp_ms(d)); //DEBUG
	while (get_long(&d->philos_ready, &d->lock, d) != d->philos_nb)
		wait_us(1, d);
	printf("%ld 🔵 monitoring: started routine 🏳️\n", get_timestamp_ms(d)); //DEBUG
}

void    *monitoring_routine(void *data_ptr)
{
	t_data	*d;

	d = (t_data *)data_ptr;
	wait_all_philos_ready(d);
	return (NULL);
}
