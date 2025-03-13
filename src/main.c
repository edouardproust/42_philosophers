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

static t_data	*start_simulation(t_data *d)
{
	int		i;

	// Create threads for each philo
	// init time first meal for each philo
	i = 0;
	while (i < d->philos_nb)
	{
		create_philo_thread(&d->philos[i]);
		d->philos[i].last_meal_time = current_time();
		i++;
	}
	thread_do(CREATE, &d->monitoring, monitoring_routine, d);
	return (d);
}

static void	stop_simulation(t_data **d)
{
	thread_do(JOIN, &(*d)->monitoring, NULL, *d);
	join_philo_threads(*d);
	free_philos(&(*d)->philos);
	free_forks(&(*d)->forks);
	free_data(d);
}

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
	start_simulation(d);
	stop_simulation(&d);
	return (EXIT_SUCCESS);
}
