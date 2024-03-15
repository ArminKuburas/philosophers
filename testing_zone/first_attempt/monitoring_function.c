/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:18 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/15 18:08:05 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	everyone_is_fed(int *thread_fed_check)
{
	
}

void	monitoring(t_pointers *data, int *argv_int)
{
	int				i;
	int				set_to_dead;
	struct timeval	current_time;

	set_to_dead = 0;
	i = 0;
	while (1)
	{
		if (i == argv_int[0])
			i = 0;
		pthread_mutex_lock(&data->monitors[i]);
		if (set_to_dead == 1)
			data->philo_died[i] = 1;
		else if (data->philo_eat_amount[i] == 0)
			data->eaten_enough[i] = 1;
		else if (everyone_is_fed(data->eaten_enough) == 1)
		{
			set_to_dead = 1;
			data->philo_died[i] = 1;
		}
		gettimeofday(&current_time, NULL);
		if (time_diff(data->philo_wait_start[i], current_time) >= argv_int[1])
		{
			set_to_dead = 1;
			data->philo_died[i] = 1;
		}
		pthread_mutex_unlock(&data->monitors[i]);
		i++;
		if (check_if_everyone_is_dead(data->philo_died) == 1)
			break ;
	}
}
