/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

void	free_philos(t_philo **philos)
{
	if (!philos || !*philos)
		return ;
	ft_free((void **)philos);
}

void	free_forks(t_fork **forks)
{
	if (!forks || !*forks)
		return ;
	ft_free((void **)forks);
}

void	free_data(t_data **data)
{
	if (!data || !*data)
		return ;
	ft_free((void **)data);
}
