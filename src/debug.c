#include "debug.h"

void	debug_fork(t_fork *f)
{
	printf("- index: %d\n", f->index);
	printf("- state: %s\n", f->state == F_FREE ? "F_FREE" : "F_TAKEN");
}

void	debug_forks(t_data *d)
{
	int	i = 0;
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
	printf("left_fork:\n"); debug_fork(p->left_fork);
	printf("right_fork:\n"); debug_fork(p->right_fork);
}

void	debug_philos(t_data *d)
{
	int	i = 0;
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