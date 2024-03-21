/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:12 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/21 14:59:58 by akuburas         ###   ########.fr       */
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
	int				time_to_eat;
	int				time_to_sleep;
	int				philo_eat_amount;
	int				*philo_died;
	long			initial_time;
	long			time_before_eat;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*monitor;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*eat_lock;
}				t_philo_data;

typedef struct s_pointers
{
	pthread_t		philosophers[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	monitor;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	eat_lock;
	int				philo_died;
	t_philo_data	philo_data[200];
}				t_pointers;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	argument_converter(int argv_int[5], char **argv, int argc);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
int		free_pointer_data(t_pointers *data, int error_val);
void	*thread_func(void *param);
long	time_diff(struct timeval initial_time, struct timeval current_time);
void	*ft_memset(void *b, int c, size_t len);
void	monitoring(t_pointers *data, int *argv_int);
long	get_current_time(void);


#endif