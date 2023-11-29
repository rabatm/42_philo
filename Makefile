NAME = philo

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS = 	src/main.c\
		src/init.c\
		src/philo.c\
		src/pilo_utils.c\
		src/libft.c

$(NAME) :
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all : $(NAME)

fclean : clean
	$(RM) $(NAME)

clean :
	$(RM) $(NAME)

re : fclean all
