/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philosopher_routine(void *philo_ptr)
{
	t_philo *philo;

	philo = (t_philo *)philo_ptr;
	printf("[routine started by philo %d]\n", philo->id); //DEBUG
	wait(philo->id * 1000);//DEBUG
	printf("[%ld] philo %d: end\n", get_timestamp(philo->data), philo->id); //DEBUG
	return (NULL);
}

void    *monitoring_routine(void *data_ptr)
{
	t_data	*data;

	data = (t_data *)data_ptr;
	(void)data; //TODO remove
	printf("[monitoring routine started]\n"); //DEBUG
	//TODO
	return (NULL);
}
