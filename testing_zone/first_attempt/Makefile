NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
		argument_converter.c \
		free_pointers.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_memset.c \
		ft_strcmp.c \
		ft_strlen.c \
		monitoring_function.c \
		philo_helper_functions.c \
		thread_function.c \

OBJS = $(SRCS:.c=.o)
all : $(NAME)
$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all
.PHONY : all clean fclean re