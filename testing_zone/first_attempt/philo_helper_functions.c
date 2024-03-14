/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:39:20 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/14 14:41:02 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_difference(struct timeval *initial_time, struct timeval current_time)
{
	int	seconds;
	int	microseconds;

	seconds = current_time.tv_sec - initial_time->tv_sec;
	microseconds = current_time.tv_usec - initial_time->tv_usec;
	if (microseconds < 0)
	{
		seconds--;
		microseconds += 1000000;
	}
	return ((seconds * 1000) * (microseconds / 1000));
}
