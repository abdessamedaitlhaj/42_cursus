SRCS =	philo/philo.c philo/utils.c philo/utils2.c


# SRCS_BONUS =


OBJS = $(SRCS:.c=.o)
# OBJS_BONUS = $(SRCS_BONUS:.c=.o)
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address
NAME = philosof
# NAME_BONUS = philo_bonus

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)

# bonus: $(NAME_BONUS)

# $(NAME_BONUS): $(OBJS_BONUS)
# 	cc $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)

$(OBJS): %.o: %.c philo/philo.h
	cc $(CFLAGS) -c $< -o $@

# $(OBJS_BONUS): %.o: %.c philo/
# 	cc $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re