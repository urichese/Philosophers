NAME	= philo

SRCS	= philo.c threads.c utils.c time_func.c

OBJS	= ${SRCS:.c=.o}

HEADER	= philo.h

CC		= gcc

RM 		= rm -f

CFLAGS	= -Wall -Werror -Wextra

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS):	$(HEADER)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re