# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 09:24:56 by akuburas          #+#    #+#              #
#    Updated: 2024/03/25 09:24:57 by akuburas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
SANITIZE = -fsanitize=thread
SRCS = main.c \
		argument_converter.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_memset.c \
		ft_strcmp.c \
		ft_strlen.c \
		monitoring_function.c \
		philo_helper_functions.c \
		thread_function.c \
		failure_handling.c

OBJS = $(SRCS:.c=.o)
all : $(NAME)
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
sanitize : $(OBJS)
	$(CC) $(CFLAGS) $(SANITIZE) $(OBJS) -o $(NAME)
clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all
.PHONY : all clean fclean re