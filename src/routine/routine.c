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

void    *routine_handler(void *philo_ptr)
{
	t_philo *philo;

	philo = (t_philo *)philo_ptr;
	printf("routine started by philo %d\n", philo->id); //DEBUG

	wait(philo->id * 1000);
	printf("philo %d: end\n", philo->id);
	return (NULL);
}
