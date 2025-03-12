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

void	debug_fork(char *title, int id, t_fork *f)
{
	char	*state;

	printf("%s", title);
	if (id >= 0)
		printf("%d", id);
	printf(":\n");
	printf("   - index: %d\n", f->index);
	state = "F_FREE";
	if (f->state == F_TAKEN)
		state = "F_TAKEN";
	printf("   - state: %s\n", state);
}

void	debug_forks(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->philos_nb)
	{
		debug_fork("fork", i, &d->forks[i]);
		i++;
	}
}

void	debug_philo(t_philo *p)
{
	char	*action;

	printf("╭── Philosopher #%d ──────────────╮\n", p->id);
	action = "A_THINKING";
	if (p->action == A_EATING)
		action = "A_EATING";
	else if (p->action == A_SLEEPING)
		action = "A_SLEEPING";
	printf("  index: %d\n", p->index);
	printf("  id: %d\n", p->id);
	printf("  state: %s\n", action);
	debug_fork("  right_fork", -1, p->right_fork);
	debug_fork("  left_fork", -1, p->left_fork);
	printf("  last_meal_time: %ld\n", p->last_meal_time);
	printf("╰────────────────────────────────╯\n");
}

void	debug_philos(t_data *d)
{
	int	i;

	i = 0;

	printf("\n─────────────────────────────────────────\n");
	while (i < d->philos_nb)
		debug_philo(&d->philos[i++]);
	printf("─────────────────────────────────────────\n");
}

void	debug_timestamp(t_data *d)
{
	printf("[timestamp: %ld]\n", get_timestamp(d));
}
