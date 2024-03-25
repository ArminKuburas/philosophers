/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   failure_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 01:30:47 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/25 09:18:23 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_failed(t_pointers *data, int i, int type)
{
	printf("Mutex init failed\n");
	while (i > 0)
		pthread_mutex_destroy(&data->forks[i--]);
	if (type == 1)
		pthread_mutex_destroy(&data->write_lock);
	if (type == 2)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->eat_lock);
	}
	return (1);
}

void	thread_failed_handler(t_pointers *data, int i)
{
	while (i > 0)
		pthread_mutex_destroy(&data->forks[i--]);
	pthread_mutex_lock(&data->monitor);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->monitor);
	printf("Thread creation failed\n");
}
