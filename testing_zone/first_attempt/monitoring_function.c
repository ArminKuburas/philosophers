/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:18 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/17 23:44:23 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	everyone_is_fed(int *thread_fed_check, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (thread_fed_check[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_if_everyone_is_dead(int *thread_dead_check, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (thread_dead_check[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void	check_starvation(t_pointers *data, int timeToDie, int i, int *setToDead)
{
	struct timeval	crnt_time;

	gettimeofday(&crnt_time, NULL);
	if (time_diff(data->philo_wait_start[i], crnt_time) >= timeToDie)
	{
		*setToDead = 1;
		data->philo_died[i] = 1;
		pthread_mutex_lock(&data->write_lock);
		printf("%ld %d died\n", time_diff(data->philo_wait_start[i],
				crnt_time), i + 1);
		pthread_mutex_unlock(&data->write_lock);
	}
}

void	check_if_eaten(t_pointers *data, int amount, int i, int *setToDead)
{
	data->eaten_enough[i] = 1;
	if (everyone_is_fed(data->eaten_enough, amount) == 1)
	{
		*setToDead = 1;
		data->philo_died[i] = 1;
	}
}

void	monitoring(t_pointers *data, int *argv_int)
{
	int				i;
	int				set_to_dead;

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
			check_if_eaten(data, argv_int[0], i, &set_to_dead);
		if (data->philo_died[i] == 0)
			check_starvation(data, argv_int[1], i, &set_to_dead);
		pthread_mutex_unlock(&data->monitors[i]);
		if (check_if_everyone_is_dead(data->philo_died, argv_int[0]) == 1)
			return ;
		i++;
	}
}
