/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:17:56 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/01/10 13:08:48 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_death(t_philo *philo, int which)
{
	if (which == 1)
	{
		pthread_mutex_lock(&philo->last_meal_m);
		pthread_mutex_lock(&philo->had_enough_m);
		if (philo->had_enough == false
			&& get_time_diff(philo->table->start_time)
			- philo->last_meal_t > philo->table->time_to_die)
			return (pthread_mutex_unlock(&philo->had_enough_m),
				pthread_mutex_unlock(&philo->last_meal_m), 1);
		pthread_mutex_unlock(&philo->last_meal_m);
		pthread_mutex_unlock(&philo->had_enough_m);
	}
	else if (which == 0)
	{
		pthread_mutex_lock(&philo->table->is_anyone_died_m);
		if (philo->table->is_anyone_died == false)
			return (pthread_mutex_unlock(&philo->table->is_anyone_died_m), 1);
		pthread_mutex_unlock(&philo->table->is_anyone_died_m);
	}
	return (0);
}

static void	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	print(*philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[(philo->id + 1)
		% philo->table->philo_count]);
	print(*philo, "has taken a fork");
	pthread_mutex_lock(&philo->last_meal_m);
	philo->last_meal_t = get_time_diff(philo->table->start_time);
	pthread_mutex_unlock(&philo->last_meal_m);
	print(*philo, "is eating");
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
	pthread_mutex_unlock(&philo->table->forks[(philo->id + 1)
		% philo->table->philo_count]);
	print(*philo, "is sleeping");
	ft_usleep(philo->table->time_to_sleep);
	print(*philo, "is thinking");
	if (philo->table->philo_count % 2 != 0)
		ft_usleep(philo->table->time_to_eat / 2);
}

void	*philo_main(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->table->time_to_eat / 2);
	while (check_death(philo, 0))
	{
		philo_routine(philo);
		philo->meals_eaten++;
		if (philo->table->must_eat != -1
			&& philo->meals_eaten == philo->table->must_eat)
			break ;
	}
	pthread_mutex_lock(&philo->had_enough_m);
	philo->had_enough = true;
	pthread_mutex_unlock(&philo->had_enough_m);
	return (NULL);
}

void	*monitor(void *arg)
{
	int			i;
	int			count;
	t_philo		*philos;

	philos = (t_philo *)arg;
	while (!philos->table->stop)
	{
		i = -1;
		count = 0;
		while (++i < philos->table->philo_count && !philos->table->stop)
		{
			if (check_death(&philos[i], 1))
				return (kill_print(philos[i], "died"), NULL);
			pthread_mutex_lock(&philos[i].had_enough_m);
			if (philos[i].had_enough == true)
				count++;
			pthread_mutex_unlock(&philos[i].had_enough_m);
		}
		if (count == philos->table->philo_count)
			break ;
	}
	return (NULL);
}
