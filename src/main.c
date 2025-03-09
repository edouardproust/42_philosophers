/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 14:12:57 by eproust           #+#    #+#             */
/*   Updated: 2025/03/08 14:13:01 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include "debug.h" //DEBUG
int	main(int ac, char **av)
{
	t_data	*d;

	if (ac < 5 || ac > 6)
	{
		printf("Usage: ./philo nb_of_philosophers strave_time eat_time "
			"sleep_time [meals_per_philosopher]\n");
		exit(EXIT_FAILURE);
	}
	d = init_data(av);
	debug_timestamp(d); //DEBUG
	debug_philos(d); // DEBUG
	usleep(2234000); //DEBUG
	debug_timestamp(d); //DEBUG
	/*
	init_timer();
	int i = 0
	while (are_all_philos_alive(philos)) {
		while (philos[i])
		{
			set_philo_activity(philos[i], )
			feed_if_forks_avail(philos[i], time_to_eat);
			->{
				
			}
			sleep_if_not_eating(time_to_sleep, philos[i]->activity)
			->{
				
			};
			i++
		}
	}
	*/
	free_data(&d);
	return (EXIT_SUCCESS);
}
