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

static t_data	*start_simulation(char **args)
{
	t_data	*data;

	data = init_data(args);
	data->forks = init_forks(data);
	data->philos = init_philos(data);
	return (data);
}

static void	stop_simulation(t_data **data)
{
	join_threads(*data);
	free_philos(&(*data)->philos);
	free_forks(&(*data)->forks);
	free_data(data);
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
	d = start_simulation(av);
	stop_simulation(&d);
	return (EXIT_SUCCESS);
}
