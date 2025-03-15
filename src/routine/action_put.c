/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	do_put_action_debug(int action_code, long tp, t_philo *p)
{
	int		id;

	id = p->id;
	if (action_code == TAKE_FIRST_FORK)
		printf("%ld\t%d took first fork (#%d)\n", tp, id, p->first_fork->index);
	else if (action_code == TAKE_SECOND_FORK)
		printf("%ld\t%d took second fork (#%d)\n", tp, id, p->second_fork->index);
	else if (action_code == EAT)
		printf("%ld\t" BLUE "%d is eating 🍝" RST " (meal %d | last %ld ms ago)\n",
			tp, id, get_int(&p->meals_done, &p->lock, p->data),
			time_since_last_meal(p, MS));
	else if (action_code == SLEEP)
		printf("%ld\t%d is sleeping (meal %ld ms ago)\n", tp, id,
			time_since_last_meal(p, MS));
	else if (action_code == THINK)
		printf("%ld\t%d is thinking (meal %ld ms ago)\n", tp, id,
			time_since_last_meal(p, MS));
	else if (action_code == DIE)
		printf("%ld\t" RED "%d died 💀" RST " (meal %ld us ago)\n", tp, id,
			time_since_last_meal(p, US));
	else
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

static	int	do_put_action(int action_code, long tp, t_philo *p)
{
	int		id;

	id = p->id;
	if (action_code == TAKE_FIRST_FORK || action_code == TAKE_SECOND_FORK)
		printf("%ld\t%d has taken a fork\n", tp, id);
	else if (action_code == EAT)
		printf("%ld\t" BLUE "%d is eating\n" RST, tp, id);
	else if (action_code == SLEEP)
		printf("%ld\t%d is sleeping\n", tp, id);
	else if (action_code == THINK)
		printf("%ld\t%d is thinking\n", tp, id);
	else if (action_code == DIE)
		printf("%ld\t" RED "%d died\n" RST, tp, id);
	else
		return (EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

void	put_action(int action_code, t_philo *p)
{
	t_data	*d;
	long	tp;
	int		ret;

	d = p->data;
	if (simulation_finished(d))
		return ;
	tp = get_timestamp_ms(p->data);
	mutex_do(LOCK, &d->print_lock, d);
	if (!DEBUG_MODE)
		ret = do_put_action(action_code, tp, p);
	else
		ret = do_put_action_debug(action_code, tp, p);
	mutex_do(UNLOCK, &d->print_lock, d);
	if (ret != EXIT_SUCCESS)
		exit_program("put_action: wrong action_code", &d);
}
