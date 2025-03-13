/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_program(char *error_msg, t_data **d)
{
	printf("philo: %s\n", error_msg);
	free_forks(&(*d)->forks);
	free_philos(&(*d)->philos);
	free_data(d);
	exit(EXIT_FAILURE);
}

void	exit_on_inval_arg(char *error_msg, char *wrong_arg, t_data **d)
{
	char	*err_prefix;

	err_prefix = "Invalid argument";
	printf("%s: %s: %s\n", err_prefix, wrong_arg, error_msg);
	free_data(d);
	exit(EXIT_FAILURE);
}
