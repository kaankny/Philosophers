/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:18:08 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/01/10 13:09:27 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>

void	kill_print(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.table->is_anyone_died_m);
	philo.table->is_anyone_died = true;
	pthread_mutex_unlock(&philo.table->is_anyone_died_m);
	pthread_mutex_lock(&philo.table->print_mutex);
	printf("%ld %d %s\n", get_time_diff(philo.table->start_time), philo.id + 1,
		str);
	pthread_mutex_unlock(&philo.table->print_mutex);
}

void	print(t_philo philo, char *str)
{
	pthread_mutex_lock(&philo.table->is_anyone_died_m);
	if ((philo.had_enough == false && philo.table->is_anyone_died == false))
	{
		pthread_mutex_lock(&philo.table->print_mutex);
		printf("%ld %d %s\n", get_time_diff(philo.table->start_time),
			philo.id + 1, str);
		pthread_mutex_unlock(&philo.table->print_mutex);
	}
	pthread_mutex_unlock(&philo.table->is_anyone_died_m);
}

int	ft_atoi(const char *str)
{
	int	num;
	int	i;

	i = 0;
	num = 0;
	while (str[i])
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

int	ft_error(char *str)
{
	printf("\033[0;31m%s\033[0m\n", str);
	return (1);
}
