SRCS =	philo.c utils1.c utils2.c inits.c parsing.c monitor.c

OBJS = $(SRCS:.c=.o)
RM = rm -f
CFLAGS = -pthread -g 



#addflags
#CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address




NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS) -fsanitize=address

$(OBJS): %.o: %.c philo.h
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re