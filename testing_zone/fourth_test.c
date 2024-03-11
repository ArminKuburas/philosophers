/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fourth_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:36:32 by akuburas          #+#    #+#             */
/*   Updated: 2024/03/11 09:40:04 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int	*pointer_to_array(void)
{
	int	pointer[1];

	*pointer = 5;
	return (pointer);
}

int	main(void)
{
	int	*i;

	i = pointer_to_array();
	printf("This is i = %d", *i);
	return (0);
}