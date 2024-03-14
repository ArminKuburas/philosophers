/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:07:28 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/13 21:41:05 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_func(void *param)
{
	t_philo_data	*data;

	data = param;
	if (data->philo_num % 2 == 1)
		usleep(10);
	while(1 && data->philo_eat_amount != 0)
	{
		pthread_mutex_lock(data->monitor)
		if (*data->philo_died == 1)
		{
			pthread_mutex_unlock(data->monitor);
			break ;
		}
		pthread_mutex_unlock(data->monitor);
		printf("%d is thinking\n", data->philo_num);
		pthread_mutex_lock(data->left_fork);
		pthread_mutex_lock(data->monitor);
		if (*data->philo_died == 1)
		{
			pthread_mutex_unlock(data->monitor);
			pthread_mutex_unlock(data->left_fork);
			break ;
		}
		printf("%d has taken a fork\n", data->philo_num);
		pthread_mutex_lock(data->right_fork);
		pthread_mutex_lock(data->monitor);
		if (*data->philo_died == 1)
		{
			pthread_mutex_unlock(data->monitor);
			pthread_mutex_unlock(data->left_fork);
			pthread_mutex_unlock(data->right_fork);
			break ;
		}
		printf("%d has taken a fork\n", data->philo_num);
		*data->time_before_eat = get_time();
		pthread_mutex_unlock(data->monitor);
		printf("%d is eating\n", data->philo_num);
		usleep(data->time_to_eat);
		pthread_mutex_unlock(data->left_fork);
		pthread_mutex_unlock(data->right_fork);
		pthread_mutex_lock(data->monitor);
		if (*data->philo_died == 1)
		{
			pthread_mutex_unlock(data->monitor);
			break ;
		}
		pthread_mutex_unlock(data->monitor);
		if (data->philo_eat_amount != -1)
			data->philo_eat_amount--;
		printf("%d is sleeping\n", data->philo_num);
	}
}
