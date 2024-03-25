/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:39:20 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/25 09:17:52 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

void	thread_printer(char *str, t_philo_data *data, pthread_mutex_t *w_lock)
{
	long	elapsed_time;
	long	current_time;

	current_time = get_current_time();
	elapsed_time = current_time - data->initial_time;
	pthread_mutex_lock(w_lock);
	printf("%ld %d %s", elapsed_time, data->philo_num, str);
	pthread_mutex_unlock(w_lock);
}

void	close_mutexes(t_pointers *data, int *argv_int)
{
	int	i;

	i = 0;
	while (i < argv_int[0])
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->eat_lock);
	pthread_mutex_destroy(&data->monitor);
}
