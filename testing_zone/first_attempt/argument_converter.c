/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_converter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 08:59:47 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/11 11:45:49 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_length(char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < argc - 1)
	{
		if (ft_strlen(argv[i]) > 10)
		{
			printf("One or several arguments given are too long\n");
			return (1);
		}
	}
	return (0);
}

int	is_argument_valid(char *arg)
{
	int	j;

	j = 0;
	while (arg[j] != '\0')
	{
		if (!ft_isdigit(arg[j]))
		{
			printf("Invalid Input: Argument contains non-digits\n");
			return (0);
		}
		j++;
	}
	return (1);
}

void	argument_converter(int argv_int[5], char **argv, int argc)
{
	int	i;

	i = 0;
	argv_int[5] = -1;
	if (check_length(argv, argc) == 1)
	{
		argv_int[0] = -1;
		return ;
	}
	while (i < argc - 1)
	{
		if (!is_argument_valid(argv[i]))
		{
			argv_int[0] = -1;
			return ;
		}
		argv_int[i] = ft_atoi(argv[i]);
		i++;
	}
}
