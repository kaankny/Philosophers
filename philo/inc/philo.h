/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkanyilm <42kocaeli.com.tr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:17:07 by kkanyilm          #+#    #+#             */
/*   Updated: 2024/01/10 12:45:45 by kkanyilm         ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_philo
{
	int					id;
	int					had_enough;
	int					meals_eaten;
	long				last_meal_t;
	pthread_mutex_t		had_enough_m;
	pthread_mutex_t		last_meal_m;
	pthread_t			thread;
	struct s_table		*table;
}						t_philo;

typedef struct s_table
{
	pthread_t			monitor_thread;
	bool				stop;
	int					philo_count;
	int					must_eat;
	bool				is_anyone_died;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_time;
	pthread_mutex_t		is_anyone_died_m;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	t_philo				*philos;
}						t_table;

void					destroy_table_mutex(t_table *table, int limit);
void					destroy_philo_mutex(t_table *table, int limit);
void					destroy_philo_thread(t_table *table, int limit);
void					destroy_philo_thread_join(t_table *table, int limit);
int						monitor_thread_init(t_table *table);	
int						table_init(t_table *table, int ac, char **av);
int						philos_init(t_table *table);
void					*philo_main(void *arg);
int						check_params(char **av);
int						ft_error(char *str);
long					get_time(void);
void					print(t_philo philo, char *str);
void					kill_print(t_philo philo, char *str);
void					ft_usleep(long time);
int						ft_atoi(const char *str);
void					clean_up(t_table *table);
long					get_time_diff(long start);
int						philo_thread_init(t_table *table);
void					*monitor(void *arg);
int						table_mutex_init(t_table *table);
#endif
