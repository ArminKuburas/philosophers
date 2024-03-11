/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 03:17:39 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/11 03:32:47 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	main(void)
{
	struct timeval		initial_time;
	struct timeval		time;
	int					i;

	i = gettimeofday(&initial_time, NULL);
	if (i == -1)
	{
		printf("Error\n");
		return (0);
	}
	printf("Time: %ld\n", initial_time.tv_sec);
	printf("Time: %ld\n", initial_time.tv_usec);
	gettimeofday(&time, NULL);
	printf("Time after sleep: %ld\n", time.tv_sec - initial_time.tv_sec);
	printf("Time after sleep: %ld\n", time.tv_usec - initial_time.tv_usec);
	return (0);
}
