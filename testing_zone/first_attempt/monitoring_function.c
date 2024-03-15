/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:18 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/15 10:29:42 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitoring(t_pointers *data, int *argv_int)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == argv_int[0])
			i = 0;
		pthread_mutex_lock(&data->monitors[i]);
		
		pthread_mutex_unlock(&data->monitors[i]);
		}
		i++;
	}
}
