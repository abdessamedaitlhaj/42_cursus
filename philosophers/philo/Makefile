SRCS =	philo.c utils.c inits.c parsing.c monitor.c routine.c

OBJS = $(SRCS:.c=.o)
RM = rm -f
CFLAGS = -pthread #-g -fsanitize=thread



#addflags
#CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address




NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS): %.o: %.c philo.h
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re