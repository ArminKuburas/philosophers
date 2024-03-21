/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:18 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/21 15:07:17 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_everyone_fed(t_pointers *data, int amount)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->monitor);
	while (i < amount)
	{
		if (data->philo_data[i].philo_eat_amount != 0)
		{
			pthread_mutex_unlock(&data->monitor);
			return (0);
		}
		i++;
	}
	data->philo_died = 1;
	pthread_mutex_unlock(&data->monitor);
	return (1);
}

int	check_starvation(t_pointers *data, int timeToDie, int i)
{
	long	current_time;

	pthread_mutex_lock(&data->monitor);
	current_time = get_current_time();
	current_time -= data->philo_data[i].time_before_eat;
	if (current_time >= timeToDie)
	{
		data->philo_died = 1;
		pthread_mutex_lock(&data->write_lock);
		printf("%ld %d died\n", current_time, i + 1);
		pthread_mutex_unlock(&data->write_lock);
		pthread_mutex_unlock(&data->monitor);
		return (1);
	}
	pthread_mutex_unlock(&data->monitor);
	return (0);
}

void	monitoring(t_pointers *data, int *argv_int)
{
	int				i;

	i = 0;
	while (1)
	{
		if (i == argv_int[0])
			i = 0;
		if (data->philo_died == 1)
			break ;
		if (check_starvation(data, argv_int[1], i) == 1)
			break ;
		if (check_everyone_fed(data, argv_int[0]) == 1)
			break ;
	}
}
