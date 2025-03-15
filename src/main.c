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

	i = 0;
	thread_do(CREATE, &d->monitoring, monitoring_routine, d);
	while (i < d->philos_nb)
		create_philo_thread(&d->philos[i++], philosopher_routine);
	set_long(&d->start_time, current_time_us(d), &d->lock, d);
	return (d);
}

static void	clean_simulation(t_data **d)
{
	join_threads(*d);
	destroy_mutexes(*d);
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
	clean_simulation(&d);
	return (EXIT_SUCCESS);
}
