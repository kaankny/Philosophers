/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:33:49 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/01/09 16:39:29 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	valid_input(char *str)
{
	int			len;
	const char	*number;
	long		num;

	num = 0;
	len = 0;
	if (*str == '-')
		return (ft_error("Negative Input!"));
	if (!(*str >= '0' && *str <= '9'))
		return (ft_error("Invalid Input"));
	number = str;
	while (*str >= '0' && *str <= '9')
	{
		++len;
		str++;
	}
	if (*str)
		return (ft_error("Invalıd Input"));
	if (len > 10)
		return (ft_error("INT_MAX Error!"));
	while (*number >= '0' && *number <= '9')
		num = (num * 10) + (*number++ - 48);
	if (num > 2147483647)
		return (ft_error("INT_MAX Error!"));
	return (0);
}

int	check_params(char **av)
{
	int		i;

	i = 0;
	while (av[++i])
	{
		if (valid_input(av[i]))
			return (1);
	}
	return (0);
}
