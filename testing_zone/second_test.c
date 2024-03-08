/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 02:58:58 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/08 03:14:51 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct s_data
{
	int				philo;
	int				counter;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
};

void	set_up_data(struct s_data *data, pthread_mutex_t *locks)
{
	data[0].philo = 1;
	data[0].counter = 0;
	data[0].left = &locks[0];
	data[0].right = &locks[1];
	data[1].philo = 2;
	data[1].counter = 0;
	data[1].left = &locks[1];
	data[1].right = &locks[0];
	pthread_mutex_init(&locks[0], NULL);
	pthread_mutex_init(&locks[1], NULL);
}

void	*thread_func(void *arg)
{
	struct s_data	*data;
	int				id;

	printf("Thread function\n");
	data = (struct s_data *)arg;
	if (data->philo == 1)
		usleep(1000);
	id = data->philo;
	printf("Thread %d: I am alive\n", id);
	while (1)
	{
		printf("Thread %d: I am waiting\n", id);
		pthread_mutex_lock(data->left);
		pthread_mutex_lock(data->right);
		printf("Thread %d: I am using the mutex\n", id);
		pthread_mutex_unlock(data->left);
		pthread_mutex_unlock(data->right);
		printf("Thread %d: I am done using the mutex\n", id);
		usleep(1000);
		data->counter++;
		if (data->counter >= 2)
			break ;
	}
	return (NULL);
}

int	main(void)
{
	struct s_data	*data;
	pthread_t		thread1;
	pthread_t		thread2;
	pthread_mutex_t	*locks;

	data = malloc(2 * sizeof(struct s_data));
	locks = malloc(2 * sizeof(pthread_mutex_t));
	set_up_data(data, locks);
	printf("after mutex init\n");
	pthread_create(&thread1, NULL, thread_func, &data[0]);
	pthread_create(&thread2, NULL, thread_func, &data[1]);
	printf("after thread create function calls.\n");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	free(data);
	free(locks);
	return (0);
}
