/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:00 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/12 11:50:35 by akuburas         ###   ########.fr       */
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
	data->philo_died = malloc(sizeof(int) * argv_int);
	if (data->philo_died == NULL)
	{
		printf("Malloc failed\n");
		free(data->philosophers);
		free(data->forks);
		free(data->monitors);
		free(data->philo_wait_start);
		return (1);
	}
	data->philo_data = malloc(sizeof(t_philo_data) * argv_int);
	if (data->philo_data == NULL)
	{
		printf("Malloc failed\n");
		free(data->philosophers);
		free(data->forks);
		free(data->monitors);
		free(data->philo_wait_start);
		free(data->philo_died);
		return (1);
	}
	return (0);
}

int	mutex_init(t_pointers *data, int *argv_int)
{
	int	i;

	i = 0;
	while (i < argv_int[0])
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("Mutex init failed\n");
			return (1);
		}
		if (pthread_mutex_init(&data->monitors[i], NULL) != 0)
		{
			printf("Mutex init failed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	roundtable(t_pointers *data, int *argv_int)
{
	int				i;

	philo_data = malloc(sizeof(t_philo_data) * argv_int[0]);
	if (philo_data == NULL)
	{
		printf("Malloc failed\n");
		return ;
	}
	if (mutex_init(data, argv_int) == 1)
	{
		free(philo_data);
		return ;
	}
	set_up_philo_data(philo_data, data, argv_int);
	create_threads(data, philo_data, argv_int);
	monitoring(data, argv_int);
	i = 0;
	while (i < argv_int[0])
	{
		pthread_join(data->philosophers[i], NULL);
		i++;
	}
	free(philo_data);
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
