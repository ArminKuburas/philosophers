/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:12 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/12 15:26:14 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo_data
{
	int				philo_num;
	int				philo_eat_amount;
	int				*philo_died;
	suseconds_t		initial_time;
	suseconds_t		*time_before_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*monitor;

}				t_philo_data;

typedef struct s_pointers
{
	pthread_t		*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*monitors;
	suseconds_t		*philo_wait_start;
	int				*philo_died;
	t_philo_data	*philo_data;
}				t_pointers;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	argument_converter(int argv_int[5], char **argv, int argc);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		free_pointer_data(t_pointers *data, int error_val);

#endif