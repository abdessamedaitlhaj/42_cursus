SRCS =	so_long.c				\
		check_map.c				\
		check_path.c			\
		fill_map.c				\
		get_line.c				\
		get_line_utils.c		\
		utils.c					\
		render_game.c			\
		errors.c				\
		events.c				\
		init_game.c

SRCS_BONUS =	bonus/so_long_bonus.c				\
				bonus/check_map_bonus.c				\
				bonus/check_path_bonus.c			\
				bonus/fill_map_bonus.c				\
				bonus/get_line_bonus.c				\
				bonus/get_line_utils_bonus.c		\
				bonus/utils_bonus.c					\
				bonus/render_game_bonus.c			\
				bonus/errors_bonus.c				\
				bonus/events_bonus.c				\
				bonus/init_game_bonus.c				\
				bonus/init_imgs_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

FLAGS = -Wall -Wextra -Werror

NAME = so_long
NAME_BONUS = so_long_bonus

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJS)
	cc $(OBJS) $(FLAGS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

$(OBJS):%.o: %.c so_long.h
	cc -Wall -Wextra -Werror -c $< -o $@

$(NAME_BONUS): $(OBJS_BONUS)
	cc $(OBJS_BONUS) -lmlx -framework OpenGL -framework AppKit -o $(NAME_BONUS)

$(OBJS_BONUS): %.o: %.c bonus/so_long_bonus.h
	cc -Wall -Wextra -Werror -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re 