/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   number.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eproust <contact@edouardproust.dev>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:03:27 by eproust           #+#    #+#             */
/*   Updated: 2024/12/02 05:35:44 by eproust          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_even(int nb)
{
	return (nb % 2 == 0);
}

static int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

static t_bool	is_valid_number(char *str)
{
	if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (FALSE);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (TRUE);
}

int	str_to_uint(char *str, t_data *d)
{
	long	res;
	int		i;

	i = 0;
	if (str[i] == '-')
		exit_on_inval_arg("signed number", str, &d);
	if (!is_valid_number(str))
		exit_on_inval_arg("not a number", str, &d);
	if (str[i] == '+')
		i++;
	res = 0;
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	if (res > INT_MAX)
		exit_on_inval_arg("int overflow", str, &d);
	return (res);
}
