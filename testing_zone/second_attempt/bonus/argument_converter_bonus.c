/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_converter_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 08:59:47 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/25 10:24:32 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_length(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strlen(argv[i]) > 10)
		{
			printf("One or several arguments given are too long\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_empty(char **argv, int argc)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "") == 0)
		{
			printf("One or several arguments are empty\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	is_argument_valid(char *arg)
{
	int	j;

	j = 0;
	while (arg[j] != '\0')
	{
		if (!ft_isdigit(arg[j]))
		{
			printf("One or several arguments contain non-digits\n");
			return (0);
		}
		j++;
	}
	return (1);
}

static void	check_integers(int argv_int[5])
{
	int	i;

	i = 0;
	while (argv_int[i] < 4)
	{
		if (argv_int[i] <= 0)
		{
			printf("One or several arguments are invalid integers\n");
			argv_int[0] = -1;
			return ;
		}
		i++;
	}
}

void	argument_converter(int argv_int[5], char **argv, int argc)
{
	int	i;

	i = 0;
	argv_int[4] = -1;
	if (check_length(argv, argc) == 1)
	{
		argv_int[0] = -1;
		return ;
	}
	if (check_empty(argv, argc) == 1)
	{
		argv_int[0] = -1;
		return ;
	}
	while (i < argc - 1)
	{
		if (!is_argument_valid(argv[i + 1]))
		{
			argv_int[0] = -1;
			return ;
		}
		argv_int[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	check_integers(argv_int);
}
