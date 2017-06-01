NAME		=				filesystem

SRC			=				line_edition/buffer_parse.c \
								line_edition/display.c \
								line_edition/display_line.c \
								line_edition/edit_line.c \
								line_edition/edit_line_pairing.c \
								line_edition/free_memory2.c \
								line_edition/free_memory.c \
								line_edition/ft_putint.c \
								line_edition/get2.c \
								line_edition/get.c \
								line_edition/get_clipboard.c \
								line_edition/get_next_line.c \
								line_edition/history2.c \
								line_edition/history.c \
								line_edition/init_term.c \
								line_edition/leaks.c \
								line_edition/line.c \
								line_edition/move2.c \
								line_edition/move.c \
								line_edition/my_exit.c \
								line_edition/pairing.c \
								line_edition/signal_fnt.c \
								line_edition/struct.c \
								line_edition/term_error.c \
								line_edition/to_is.c \
								main.c \
								

OBJ_NAME	=		$(SRC:.c=.o)
OBJ_PATH	=		obj/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAGS		=		-Wall -Wextra -Werror

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	make -C libft
	gcc -o $(NAME) $(FLAGS)  $(OBJ) -lcurses -lft -L ./libft -I includes

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj/line_edition
	gcc $(FLAGS) -c $< -o $@ -I includes

clean:
	make -C libft/ fclean
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
