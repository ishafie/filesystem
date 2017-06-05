NAME		=				filesystem

SRC			=				action_blocks.c \
								create_blocks.c \
								create_filesystem.c \
								create_folder.c \
								create_inode.c \
								display_file.c \
								err.c \
								my_mkdir.c \
								my_ls.c \
								my_add.c \
								my_rm.c \
								my_cat.c \
								my_rename.c \
								tools.c \
								main.c \
								line_edition/buffer_parse.c \
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

OBJ_NAME	=		$(SRC:.c=.o)
OBJ_PATH	=		obj/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAGS		=		-Wall -Wextra -g

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	@make -C libft
	@gcc -o $(NAME) $(FLAGS)  $(OBJ) -lcurses -lft -L ./libft -I includes

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
