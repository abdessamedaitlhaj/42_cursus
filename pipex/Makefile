SRCS =	mandatory/utils.c mandatory/pipex.c mandatory/helpers.c mandatory/ft_split.c

SRCS_BONUS =	bonus/pipex_bonus.c bonus/utils_bonus.c bonus/helpers_bonus.c bonus/ft_split_bonus.c bonus/execute_cmds_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = pipex
NAME_BONUS = pipex_bonus

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS)
	cc $(FLAGS) $(OBJS_BONUS) -o $(NAME_BONUS)

$(OBJS): %.o: %.c mandatory/pipex.h
	cc $(FLAGS) -c $< -o $@

$(OBJS_BONUS): %.o: %.c bonus/pipex_bonus.h
	cc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)	

re: fclean all

.PHONY: clean fclean re all bonus

