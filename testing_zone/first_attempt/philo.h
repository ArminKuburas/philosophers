/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 23:08:12 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/11 11:35:33 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int				philo_num;
	int				*philo_died;
	suseconds_t		initial_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*monitor;
}				t_data;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
void	argument_converter(int argv_int[5], char **argv, int argc);
size_t	ft_strlen(const char *s);

#endif