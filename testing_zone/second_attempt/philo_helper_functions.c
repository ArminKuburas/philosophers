/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:39:20 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/23 01:36:42 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_diff(struct timeval initial_time, struct timeval current_time)
{
	long	seconds;
	long	microseconds;

	seconds = current_time.tv_sec - initial_time.tv_sec;
	microseconds = current_time.tv_usec - initial_time.tv_usec;
	if (microseconds < 0)
	{
		seconds--;
		microseconds += 1000000;
	}
	return ((seconds * 1000) + (microseconds / 1000));
}

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
