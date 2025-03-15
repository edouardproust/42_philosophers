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

static void	put_action_str(t_philo *philo, char *str, char *color)
{
	if (color == NULL)
		color = "";
	printf(
		BOLD "%ld\t" RESET "%s%d %s\n" RESET,
		get_timestamp_ms(philo->data), color, philo->id, str
	);
}

static void put_action_debug(int action_code, t_philo *p)
{
	long	tp;
	int		id;
	t_data	*d;
	long	lmt;
	long	lmd;

	tp = get_timestamp_ms(p->data);
	id = p->id;
	d = p->data;
	lmt = get_long(&p->last_meal_time, &p->lock, d);
	lmd = (current_time_us(d) - lmt) / 1000;
	mutex_do(LOCK, &d->print_lock, d);
	if (action_code == TAKE_FIRST_FORK)
		printf("%ld\t%d took first fork (#%d)\n", tp, id, p->first_fork->index);
	else if (action_code == TAKE_SECOND_FORK)
		printf("%ld\t%d took second fork (#%d)\n", tp, id, p->second_fork->index);
	else if (action_code == EAT)
		printf("%ld\t" BOLD BLUE "%d is eating 🍝" RESET " (meal %ld | last %ld ms ago)\n",
			tp, id, get_long(&p->meals_done, &p->lock, d), lmd);
	else if (action_code == SLEEP)
		printf("%ld\t%d is sleeping (meal %ld ms ago)\n", tp, id, lmd);
	else if (action_code == THINK)
		printf("%ld\t%d is thinking (meal %ld ms ago)\n", tp, id, lmd);
	else if (action_code == DIE)
		printf("%ld\t%d died 💀 (meal %ld us ago)\n", tp, id,
			(current_time_us(d) - lmt));
	else
		exit_program("put_action: wrong action_code", &d);
	mutex_do(UNLOCK, &d->print_lock, d);
}

void put_action(int action_code, t_philo *philo)
{
	if (simulation_finished(philo->data))
		return ;
	if (DEBUG_MODE)
	{
		put_action_debug(action_code, philo);
		return ;
	}
	mutex_do(LOCK, &philo->data->print_lock, philo->data);
	if (action_code == TAKE_FIRST_FORK || action_code == TAKE_SECOND_FORK)
		put_action_str(philo, "has taken a fork", NULL);
	else if (action_code == EAT)
		put_action_str(philo, "is eating", BOLD BLUE);
	else if (action_code == SLEEP)
		put_action_str(philo, "is sleeping", NULL);
	else if (action_code == THINK)
		put_action_str(philo, "is thinking", NULL);
	else if (action_code == DIE)
		put_action_str(philo, "died", NULL);
	else
		exit_program("put_action: wrong action_code", &philo->data);
	mutex_do(UNLOCK, &philo->data->print_lock, philo->data);
}