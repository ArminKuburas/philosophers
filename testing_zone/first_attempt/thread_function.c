/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:07:28 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/13 12:47:23 by akuburas         ###   ########.fr       */
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
	}
}
