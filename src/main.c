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
	/*
	create threads (1 per philosoper)
	create mutexes (1 per fork)
	While (are_all_philos_alive)
	{
		foreach philo (= thread)
		{
			eat_if_forks_avail
			sleep_after_eating
			thinking_after_sleeping
			die_if_starved
		}
	}
	delete threads
	delete mutexes
	*/
	free_data(&d);
	return (EXIT_SUCCESS);
}
