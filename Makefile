NAME		= pipex

LIBFT		= libft

NAME_LIBFT	= libft/libft.a

CCL			= clang

CCM			= gcc

SRC			= pipex.c \
			pipex_utils.c \
			pipex_functions.c \

OBJ			= $(SRC:.c=.o)

DEP			= $(SRC:.c=.d)

all:		$(NAME)

%.o : %.c
			$(CCL) -I . -o $@ -c $<

$(NAME_LIBFT):
			make -C $(LIBFT)

$(NAME):	$(NAME_LIBFT) $(OBJ)
			$(CCL) $(OBJ) $(NAME_LIBFT) -o $(NAME)

clean:
			rm -rf $(OBJ)
			rm -rf $(DEP)
			make clean -C $(LIBFT)

fclean:		clean
			rm -rf $(NAME)
			make fclean -C $(LIBFT)

re:			fclean all

run:
			make && make clean && clear
-include $(DEP)

.PHONY: all clean fclean re
