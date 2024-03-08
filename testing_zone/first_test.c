/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:37:44 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/06 18:09:07 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t	lock;
int counter1 = 0;
int counter2 = 0;

void	*thread_func(void *arg)
{
	int	id; 
	usleep(1000);
	printf("Thread function\n");
	id = *((int *)arg);
	printf("Thread %d: I am alive\n", id);
	while (1)
	{
		printf("Thread %d: I am waiting\n", id);
		pthread_mutex_lock(&lock);
		printf("Thread %d: I am using the mutex\n", id);
		pthread_mutex_unlock(&lock);
		printf("Thread %d: I am done using the mutex\n", id);
		usleep(1000);
		if (id == 1)
		{
			counter1++;
			if (counter1 >= 2)
				break ;
		}
		else if (id == 2)
		{
			counter2++;
			if (counter2 >= 2)
				break ;
		}
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	int	i;
	int	j;

	i = 1;
	j = 2;
	if (pthread_mutex_init(&lock, NULL) != 0)
	{
		printf("Failed to initialize mutex\n");
		return (1);
	}
	printf("after mutex init\n");
	if (pthread_create(&thread1, NULL, thread_func, &i) != 0)
	{
		printf("Failed to create thread 1\n");
		return (1);
	}
	printf("after thread 1\n");
	if (pthread_create(&thread2, NULL, thread_func, &j) != 0) 
	{
		printf("Failed to create thread 2\n");
		return (1);
	}
	printf("after thread 2\n");
	usleep(1000000);
	printf("Main thread: I am done\n");
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Threads are done\n");
	pthread_mutex_destroy(&lock);
	printf("Mutex destroyed\n");
	return (0);
}
