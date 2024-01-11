/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:17:42 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/01/10 12:35:03 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <stdlib.h>

int	table_init(t_table *table, int ac, char **av)
{
	table->philo_count = ft_atoi(av[1]);
	if (table->philo_count < 1 || table->philo_count > 200)
		return (ft_error(
				"Error: Number of philosophers must be between 1 and 200"));
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->time_to_die < 60 || table->time_to_eat < 60
		|| table->time_to_sleep < 60)
		return (ft_error("Error: Time must be greater than 60ms"));
	table->must_eat = -1;
	if (ac == 6)
		table->must_eat = ft_atoi(av[5]);
	table->start_time = get_time();
	table->is_anyone_died = false;
	table->stop = false;
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->philo_count);
	if (!table->forks)
		return (ft_error("Error: Malloc failed"));
	table->philos = (t_philo *)malloc(sizeof(t_philo)
			* table->philo_count);
	if (!table->philos)
		return (free(table->forks), ft_error("Error: Malloc failed"));
	return (0);
}

int	philos_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = i;
		table->philos[i].table = table;
		table->philos[i].last_meal_t = table->start_time;
		table->philos[i].meals_eaten = 0;
		if (pthread_mutex_init(&table->philos[i].had_enough_m, NULL))
			return (destroy_philo_mutex(table, i),
				ft_error("Error: Mutex init failed"));
		if (pthread_mutex_init(&table->philos[i].last_meal_m, NULL))
			return (pthread_mutex_destroy(&table->philos[i].had_enough_m),
				destroy_philo_mutex(table, i),
				ft_error("Error: Mutex init failed"));
	}
	return (0);
}

int	table_mutex_init(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->is_anyone_died_m, NULL))
		return (ft_error("Error: Mutex init failed"));
	if (pthread_mutex_init(&table->print_mutex, NULL))
		return (pthread_mutex_destroy(&table->is_anyone_died_m),
			ft_error("Error: Mutex init failed"));
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i++], NULL))
			return (destroy_table_mutex(table, i),
				ft_error("Error: Mutex init failed"));
	}
	return (0);
}

int	philo_thread_init(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_count)
		if (pthread_create(&table->philos[i].thread, NULL, &philo_main,
				&table->philos[i]))
			return (destroy_philo_thread(table, i),
				ft_error("Error: Thread init failed"), 1);
	i = -1;
	while (++i < table->philo_count)
		if (pthread_join(table->philos[i].thread, NULL))
			return (destroy_philo_thread_join(table, i),
				ft_error("Error: Thread init failed"));
	return (0);
}

int	monitor_thread_init(t_table *table)
{
	if (pthread_create(&table->monitor_thread, NULL, &monitor, table->philos))
		return (destroy_philo_mutex(table, table->philo_count),
			ft_error("Error: Thread init failed"));
	return (0);
}
