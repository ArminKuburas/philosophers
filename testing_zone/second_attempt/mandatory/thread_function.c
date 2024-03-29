/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:07:28 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/23 01:24:36 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor_data_handler(t_philo_data *data)
{
	if (data->philo_eat_amount != -1 && data->philo_eat_amount > 0)
		data->philo_eat_amount -= 1;
	data->time_before_eat = get_current_time();
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

int	ft_usleep(int miliseconds)
{
	long	start;

	start = get_current_time();
	while ((get_current_time() - start) < miliseconds)
		usleep(500);
	usleep(500);
	return (0);
}

void	thread_loop_function(t_philo_data *data)
{
	while (1)
	{
		if (philo_dead(data, 1) == 1)
			break ;
		pthread_mutex_lock(data->left_fork);
		if (philo_dead(data, 2) == 1)
			break ;
		thread_printer("has taken a fork\n", data, data->write_lock);
		pthread_mutex_lock(data->right_fork);
		if (philo_dead(data, 3) == 1)
			break ;
		thread_printer("has taken a fork\n", data, data->write_lock);
		thread_printer("is eating\n", data, data->write_lock);
		ft_usleep(data->time_to_eat);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		if (philo_dead(data, 1) == 1)
			break ;
		thread_printer("is sleeping\n", data, data->write_lock);
		ft_usleep(data->time_to_sleep);
		if (philo_dead(data, 1) == 1)
			break ;
		thread_printer("is thinking\n", data, data->write_lock);
	}
}

void	*thread_func(void *param)
{
	t_philo_data	*data;

	data = (t_philo_data *)param;
	if (data->left_fork == data->right_fork)
	{
		thread_printer("has taken a fork\n", data, data->write_lock);
		return (NULL);
	}
	if (data->philo_num % 2 == 0 || data->philo_num == data->philo_amount)
		usleep(10000);
	thread_loop_function(data);
	return (NULL);
}
