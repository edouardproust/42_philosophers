/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	debug_fork(t_fork *f)
{
	char	*state;

	printf("- index: %d\n", f->index);
	state = "F_FREE";
	if (f->state == F_TAKEN)
		state = "F_TAKEN";
	printf("- state: %s\n", state);
}

void	debug_forks(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philos_nb)
		debug_fork(&d->forks[i++]);
}

void	debug_philo(t_philo *p)
{
	char	*action;

	action = "A_THINKING";
	if (p->action == A_EATING)
		action = "A_EATING";
	else if (p->action == A_SLEEPING)
		action = "A_SLEEPING";
	printf("Philosopher nb.%d:\n", p->number);
	printf("index: %d\n", p->index);
	printf("number: %d\n", p->number);
	printf("state: %s\n", action);
	printf("left_fork:\n");
	debug_fork(p->left_fork);
	printf("right_fork:\n");
	debug_fork(p->right_fork);
}

void	debug_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philos_nb)
	{
		debug_philo(&d->philos[i++]);
		printf("\n");
	}
}

void	debug_timestamp(t_data *d)
{
	printf("[timestamp: %ld]\n", get_timestamp_ms(d));
}
