SRCS =	utils/ft_atoi.c utils/ft_lstadd_back.c		   \
		utils/ft_lstclear.c utils/ft_lstlast.c		   \
		utils/ft_lstnew.c utils/ft_lstsize.c		   \
		utils/ft_split.c utils/ft_strlen.c			   \
		parsing.c push_swap.c operations_one.c		   \
		operations_two.c utils.c algo_one.c algo_two.c


SRCS_BONUS =	bonus/utils/ft_atoi_bonus.c									\
				bonus/utils/ft_lstadd_back_bonus.c							\
				bonus/utils/ft_lstclear_bonus.c								\
				bonus/utils/ft_lstlast_bonus.c								\
				bonus/utils/ft_lstnew_bonus.c								\
				bonus/utils/ft_lstsize_bonus.c								\
				bonus/utils/ft_split_bonus.c								\
				bonus/utils/ft_strncmp_bonus.c								\
				bonus/utils/ft_strlen_bonus.c								\
				bonus/parsing_bonus.c bonus/checker_bonus.c				 	\
				bonus/operations_one_bonus.c bonus/operations_two_bonus.c	\
				bonus/utils_bonus.c bonus/utils/get_line_bonus.c			\
				bonus/utils/get_line_utils_bonus.c


OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

NAME = push_swap
NAME_BONUS = checker

all: $(NAME)

$(NAME): $(OBJS)
	cc -Wall -Wextra -Werror -o $(NAME) $(OBJS)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	cc -Wall -Wextra -Werror -o $(NAME_BONUS) $(OBJS_BONUS)

$(OBJS): %.o: %.c push_swap.h
	cc -Wall -Wextra -Werror -c $< -o $@

$(OBJS_BONUS): %.o: %.c bonus/checker_bonus.h
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re