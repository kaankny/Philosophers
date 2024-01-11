NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = src/main.c src/init.c src/utils.c src/routine.c src/checker.c src/time.c src/destroyer.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re