/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:12 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/12 04:39:11 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				philo_num;
	int				*philo_died;
	suseconds_t		initial_time;
	suseconds_t		*time_before_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*monitor;
}				t_philo;

typedef struct s_pointers
{
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*monitors;
	suseconds_t		*philo_wait_start;
}				t_pointers;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	argument_converter(int argv_int[5], char **argv, int argc);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);

#endif