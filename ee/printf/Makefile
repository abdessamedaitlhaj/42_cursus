SRCS = ./ft_printf.c pr_adr.c pr_char.c pr_int.c pr_hex.c pr_str.c pr_uns_nbr.c
OBJS = $(SRCS:.c=.o)
NAME = libftprintf.a

all : $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	cc -Wall -Wextra -Werror -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
