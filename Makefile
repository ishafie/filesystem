# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishafie <ishafie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/25 23:31:13 by ishafie           #+#    #+#              #
#    Updated: 2016/05/26 00:21:58 by ishafie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=				filesystem

SRC			=				main.c						\
								create_filesystem.c \
								err.c \
								create_inode.c \
								create_folder.c \
								create_blocks.c \


OBJ_NAME	=		$(SRC:.c=.o)
OBJ_PATH	=		obj/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))

FLAGS		=		-Wall -Wextra -g

.PHONY: all, clean, fclean, re

$(NAME): $(OBJ)
	make -C libft
	gcc -o $(NAME) $(FLAGS) $(OBJ) -lft -L ./libft -I includes

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	gcc $(FLAGS) -c $< -o $@ -I includes

clean:
	make -C libft/ fclean
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
