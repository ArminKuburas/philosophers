/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:07:28 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/16 23:11:27 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_data_handler(t_philo_data *data)
{
	if (*data->philo_eat_amount != -1 && *data->philo_eat_amount > 0)
		*data->philo_eat_amount -= 1;
	gettimeofday(data->time_before_eat, NULL);
}

int	philo_dead(t_philo_data *data, int type)
{
	pthread_mutex_lock(data->monitor);
	if (type == 1 && *data->philo_died == 1)
	{
		pthread_mutex_unlock(data->monitor);
		return (1);
	}
	if (type == 2 && *data->philo_died == 1)
	{
		pthread_mutex_unlock(data->monitor);
		pthread_mutex_unlock(data->left_fork);
		return (1);
	}
	if (type == 3 && *data->philo_died == 1)
	{
		pthread_mutex_unlock(data->monitor);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		return (1);
	}
	if (type == 3)
		monitor_data_handler(data);
	pthread_mutex_unlock(data->monitor);
	return (0);
}

void	thread_printer(char *str, t_philo_data *data)
{
	long			elapsed_time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	elapsed_time = time_diff(data->initial_time, current_time);
	printf("%ld %d %s", elapsed_time, data->philo_num, str);
}

void	thread_loop_function(t_philo_data *data)
{
	while (1)
	{
		if (philo_dead(data, 1) == 1)
			break ;
		thread_printer("is thinking\n", data);
		pthread_mutex_lock(data->left_fork);
		if (philo_dead(data, 2) == 1)
			break ;
		thread_printer("has taken a fork\n", data);
		pthread_mutex_lock(data->right_fork);
		if (philo_dead(data, 3) == 1)
			break ;
		thread_printer("has taken a fork\n", data);
		thread_printer("is eating\n", data);
		usleep(data->time_to_eat * 1000);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		if (philo_dead(data, 1) == 1)
			break ;
		if (*data->philo_eat_amount != -1)
			*data->philo_eat_amount -= 1;
		thread_printer("is sleeping\n", data);
		usleep(data->time_to_sleep * 1000);
	}
}

void	*thread_func(void *param)
{
	t_philo_data	*data;

	data = param;
	if (data->philo_num % 2 == 1)
		usleep(10);
	thread_loop_function(data);
	return (NULL);
}
