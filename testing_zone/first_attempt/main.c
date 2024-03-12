/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:00 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/12 05:10:41 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	use_malloc(t_pointers *data, int argv_int)
{
	data->philosophers = malloc(sizeof(pthread_t) * argv_int);
	if (data->philosophers == NULL)
	{
		printf("Malloc failed\n");
		return (1);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * argv_int);
	if (data->forks == NULL)
	{
		printf("Malloc failed\n");
		free(data->philosophers);
		return (1);
	}
	data->monitors = malloc(sizeof(pthread_mutex_t) * argv_int);
	if (data->monitors == NULL)
	{
		printf("Malloc failed\n");
		free(data->philosophers);
		free(data->forks);
		return (1);
	}
	data->philo_wait_start = malloc(sizeof(suseconds_t) * argv_int);
	if (data->philo_wait_start == NULL)
	{
		printf("Malloc failed\n");
		free(data->philosophers);
		free(data->forks);
		free(data->monitors);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				argv_int[5];
	t_pointers		data;

	if (argc < 5 || argc > 6)
	{
		printf("You have either given too many arguments or too few\n");
		return (1);
	}
	argument_converter(argv_int, argv, argc);
	if (argv_int[0] == -1)
		return (1);
	if (use_malloc(&data, argv_int[0]) == 1)
		return (1);
	//roundtable(&data, argv_int);
	int i = 0;
	while (i < argv_int[0])
	{
		printf("philosophers[%d] = %p\n", i, &data.philosophers[i]);
		printf("forks[%d] = %p\n", i, &data.forks[i]);
		printf("monitors[%d] = %p\n", i, &data.monitors[i]);
		printf("philo_wait_start[%d] = %p\n", i, &data.philo_wait_start[i]);
		i++;
	}
	i = 0;
	while (i < argc - 1)
	{
		printf("argv_int[%d] = %d\n", i, argv_int[i]);
		i++;
	}
	free(data.philosophers);
	free(data.forks);
	free(data.monitors);
	free(data.philo_wait_start);
	return (0);
}
