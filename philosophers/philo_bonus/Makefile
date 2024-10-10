SRCS =	philo_bonus.c utils_bonus.c parsing_bonus.c monitor_bonus.c

OBJS = $(SRCS:.c=.o)
RM = rm -f
CFLAGS = -pthread -g 



#addflags
#CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address




NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJS): %.o: %.c philo_bonus.h
	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re