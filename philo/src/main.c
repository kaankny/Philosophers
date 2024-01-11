/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:17:33 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/01/10 13:08:36 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdio.h>
#include <stdlib.h>

static void	one_philo(t_table *table)
{
	printf("%d %d %s\n", 0, 1, "has taken a fork");
	ft_usleep(table->time_to_die);
	printf("%ld %d %s\n", table->time_to_die + 1, 0, "died");
	free(table->forks);
	free(table->philos);
}

int	main(int ac, char **av)
{
	t_table		table;

	if (ac == 5 || ac == 6)
	{
		if (check_params(av))
			return (1);
		if (table_init(&table, ac, av))
			return (1);
		if (table.philo_count == 1)
			return (one_philo(&table), 0);
		if (table_mutex_init(&table))
			return (1);
		if (philos_init(&table))
			return (1);
		if (monitor_thread_init(&table))
			return (1);
		if (philo_thread_init(&table))
			return (1);
	}
	else
		return (ft_error("Error: Wrong number of arguments"));
	return (clean_up(&table), 0);
}
