/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 09:27:46 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/25 10:32:35 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_philo_data
{
	int				philo_num;
	int				philo_amount;
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_eat_amount;
	int				*philo_died;
	long			initial_time;
	long			time_before_eat;
	sem_t			*forks;
	sem_t			*monitor;
	sem_t			*write;
}				t_philo_data;

typedef struct s_pointers
{
	pid_t			philosophers[200];
	sem_t			*forks;
	sem_t			*monitor;
	sem_t			*write;
	int				philo_died;
	t_philo_data	philo_data[200];
}				t_pointers;

void	argument_converter(int argv_int[5], char **argv, int argc);

#endif