/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pointers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:33:59 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/17 14:06:48 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_pointer_data(t_pointers *data, int error_val)
{
	if (data->forks != NULL)
		free(data->forks);
	if (data->monitors != NULL)
		free(data->monitors);
	if (data->philo_data != NULL)
		free(data->philo_data);
	if (data->philo_died != NULL)
		free(data->philo_died);
	if (data->philo_wait_start != NULL)
		free(data->philo_wait_start);
	if (data->philosophers != NULL)
		free(data->philosophers);
	if (data->philo_eat_amount != NULL)
		free(data->philo_eat_amount);
	if (data->eaten_enough != NULL)
		free(data->eaten_enough);
	//if (error_val != 0)
	//	error_printer(error_val);
	if (error_val == 1)
	{
		printf("Malloc Failed\n");
		return (1);
	}
	if (error_val == 2)
	{
		printf("Mutex init failed\n");
		return (1);
	}
	return (0);
}
