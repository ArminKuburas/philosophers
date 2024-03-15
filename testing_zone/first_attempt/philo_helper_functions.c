/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:39:20 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/15 10:15:42 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_diff(struct timeval *initial_time, struct timeval current_time)
{
	long	seconds;
	long	microseconds;

	seconds = current_time.tv_sec - initial_time->tv_sec;
	microseconds = current_time.tv_usec - initial_time->tv_usec;
	if (microseconds < 0)
	{
		seconds--;
		microseconds += 1000000;
	}
	return ((seconds * 1000) * (microseconds / 1000));
}
