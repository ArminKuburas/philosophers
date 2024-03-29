/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:00 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/18 14:13:22 by akuburas         ###   ########.fr       */
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
	data->philo_wait_start = malloc(sizeof(struct timeval) * argv_int);
	if (data->philo_wait_start == NULL)
		return (free_pointer_data(data, 1));
	data->philo_died = malloc(sizeof(int) * argv_int);
	if (data->philo_died == NULL)
		return (free_pointer_data(data, 1));
	data->philo_data = malloc(sizeof(t_philo_data) * argv_int);
	if (data->philo_data == NULL)
		return (free_pointer_data(data, 1));
	data->philo_eat_amount = malloc(sizeof(int) * argv_int);
	if (data->philo_eat_amount == NULL)
		return (free_pointer_data(data, 1));
	data->eaten_enough = malloc(sizeof(int) * argv_int);
	if (data->eaten_enough == NULL)
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
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		printf("Mutex init failed\n");
		return (1);
	}
	return (0);
}

int	set_up_philo_data(t_pointers *data, int *argv_int)
{
	int				i;
	struct timeval	time;

	i = 0;
	gettimeofday(&time, NULL);
	ft_memset(data->eaten_enough, 0, argv_int[0] * sizeof(int));
	while (i < argv_int[0])
	{
		data->philo_data[i].philo_num = i + 1;
		data->philo_data[i].time_to_eat = argv_int[2];
		data->philo_data[i].time_to_sleep = argv_int[3];
		data->philo_data[i].philo_eat_amount = &data->philo_eat_amount[i];
		*data->philo_data[i].philo_eat_amount = argv_int[4];
		data->philo_data[i].philo_died = &data->philo_died[i];
		data->philo_data[i].initial_time = time;
		data->philo_data[i].time_before_eat = &data->philo_wait_start[i];
		data->philo_data[i].time_before_eat->tv_usec = time.tv_usec;
		data->philo_data[i].time_before_eat->tv_sec = time.tv_sec;
		data->philo_data[i].left_fork = &data->forks[i];
		data->philo_data[i].right_fork = &data->forks[(i + 1) % argv_int[0]];
		data->philo_data[i].monitor = &data->monitors[i];
		data->philo_data[i].write_lock = &data->write_lock;
		i++;
	}
	return (0);
}

int	create_threads(t_pointers *data, int *argv_int)
{
	int	i;

	i = 0;
	while (i < argv_int[0])
	{
		if (pthread_create(&data->philosophers[i], NULL,
				thread_func, &data->philo_data[i]) != 0)
			return (1);
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
		pthread_mutex_destroy(&data->monitors[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_lock);
}

int	roundtable(t_pointers *data, int *argv_int)
{
	int				i;

	if (mutex_init(data, argv_int) == 1)
		return (free_pointer_data(data, 2));
	if (set_up_philo_data(data, argv_int) == 1)
		return (free_pointer_data(data, 3));
	if (create_threads(data, argv_int) == 1)
		return (free_pointer_data(data, 4));
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
	if (use_malloc(&data, argv_int[0]) == 1)
		return (1);
	roundtable(&data, argv_int);
	return (free_pointer_data(&data, 0));
}
