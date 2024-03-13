/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:00 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/13 09:12:20 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	use_malloc(t_pointers *data, int argv_int)
{
	data->philosophers = malloc(sizeof(pthread_t) * argv_int);
	if (data->philosophers == NULL)
		return (free_pointer_data(data, 1));
	data->forks = malloc(sizeof(pthread_mutex_t) * argv_int);
	if (data->forks == NULL)
		return (free_pointer_data(data, 1));
	data->monitors = malloc(sizeof(pthread_mutex_t) * argv_int);
	if (data->monitors == NULL)
		return (free_pointer_data(data, 1));
	data->philo_wait_start = malloc(sizeof(suseconds_t) * argv_int);
	if (data->philo_wait_start == NULL)
		return (free_pointer_data(data, 1));
	data->philo_died = malloc(sizeof(int) * argv_int);
	if (data->philo_died == NULL)
		return (free_pointer_data(data, 1));
	data->philo_data = malloc(sizeof(t_philo_data) * argv_int);
	if (data->philo_data == NULL)
		return (free_pointer_data(data, 1));
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

void	set_up_philo_data(t_pointers *data, int *argv_int)
{
	int			i;
	suseconds_t	time;

	i = 0;
	if (gettimeofday(&time, NULL) == -1)
		return (1);
	while (i < argv_int[0])
	{
		data->philo_data[i].philo_num = i + 1;
		data->philo_data[i].time_to_eat = argv_int[2];
		data->philo_data[i].time_to_sleep = argv_int[3];
		data->philo_data[i].philo_eat_amount = argv_int[4];
		data->philo_data[i].philo_died = &data->philo_died[i];
		data->philo_data[i].initial_time = time;
		data->philo_data[i].time_before_eat = &data->philo_wait_start[i];
		data->philo_data[i].left_fork = &data->forks[i];
		data->philo_data[i].right_fork = &data->forks[(i + 1) % argv_int[0]];
		data->philo_data[i].monitor = &data->monitors[i];
		i++;
	}
	return (0);
}

int	roundtable(t_pointers *data, int *argv_int)
{
	int				i;

	if (mutex_init(data, argv_int) == 1)
		return (free_pointer_data(data, 2));
	if (set_up_philo_data(data, argv_int) == 1)
		return (free_pointer_data(data, 3))
	// create_threads(data, argv_int);
	// monitoring(data, argv_int);
	i = 0;
	while (i < argv_int[0])
	{
		pthread_join(data->philosophers[i], NULL);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				argv_int[5];
	t_pointers		data;

	data = (t_pointers){};
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
	return (free_pointer_data(&data, 0));
}
