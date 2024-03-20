/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:00 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/20 15:42:52 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mutex_failed(t_pointers *data, int i, int type)
{
	printf("Mutex init failed\n");
	while (i > 0)
		pthread_mutex_destroy(&data->forks[i--]);
	if (type == 1)
		pthread_mutex_destroy(&data->write_lock);
	if (type == 2)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->eat_lock);
	}
	return (1);
}

int	mutex_init(t_pointers *data, int *argv_int)
{
	int	i;

	i = 0;
	while (i < argv_int[0])
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (mutex_failed(data, i, 0));
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (mutex_failed(data, i, 0));
	if (pthread_mutex_init(&data->eat_lock, NULL) != 0)
		return (mutex_failed(data, i, 1));
	if (pthread_mutex_init(&data->monitor, NULL) != 0)
		return (mutex_failed(data, i, 2));
	return (0);
}

int	set_up_philo_data(t_pointers *data, int *argv_int)
{
	int				i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	while (i < argv_int[0])
	{
		data->philo_data[i].philo_num = i + 1;
		data->philo_data[i].time_to_eat = argv_int[2];
		data->philo_data[i].time_to_sleep = argv_int[3];
		data->philo_data[i].philo_eat_amount = argv_int[4];
		data->philo_data[i].philo_died = &data->philo_died;
		data->philo_data[i].initial_time = time;
		data->philo_data[i].time_before_eat = time;
		data->philo_data[i].left_fork = &data->forks[i];
		data->philo_data[i].right_fork = &data->forks[(i + 1) % argv_int[0]];
		data->philo_data[i].monitor = &data->monitor;
		data->philo_data[i].write_lock = &data->write_lock;
		data->philo_data[i].eat_lock = &data->eat_lock;
		i++;
	}
	return (0);
}

void	thread_failed_handler(t_pointers *data, int i)
{
	while (i > 0)
		pthread_mutex_destroy(&data->forks[i--]);
	pthread_mutex_lock(&data->monitor);
	data->philo_died = 1;
	pthread_mutex_unlock(&data->monitor);
	printf("Thread creation failed\n");
}

int	create_threads(t_pointers *data, int *argv_int)
{
	int	i;

	i = 0;
	while (i < argv_int[0])
	{
		if (pthread_create(&data->philosophers[i], NULL,
				thread_func, &data->philo_data[i]) != 0)
		{
			printf("Thread creation failed\n");
			thread_failed_handler(data, i - 1);
			return (1);
		}
		i++;
	}
	return (0);
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

int	roundtable(t_pointers *data, int *argv_int)
{
	int				i;

	if (mutex_init(data, argv_int) == 1)
		return (1);
	set_up_philo_data(data, argv_int);
	if (create_threads(data, argv_int) == 1)
		return (1);
	monitoring(data, argv_int);
	i = 0;
	while (i < argv_int[0])
	{
		pthread_join(data->philosophers[i], NULL);
		i++;
	}
	close_mutexes(data, argv_int);
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
	roundtable(&data, argv_int);
	return (0);
}
