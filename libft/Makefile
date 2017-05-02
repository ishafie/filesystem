# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rle-mino <rle-mino@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 09:50:20 by rle-mino          #+#    #+#              #
#    Updated: 2016/05/24 22:29:15 by rle-mino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=		ft_memset.c			\
			ft_bzero.c			\
			ft_cpy_tab.c		\
			ft_memcpy.c			\
			ft_memccpy.c		\
			ft_memmove.c		\
			ft_memchr.c			\
			ft_memcmp.c			\
			ft_strlen.c			\
			ft_strdup.c			\
			ft_strcpy.c			\
			ft_strncpy.c		\
			ft_strcat.c			\
			ft_strncat.c		\
			ft_strlcat.c		\
			ft_strchr.c			\
			ft_strrchr.c		\
			ft_strstr.c			\
			ft_strnstr.c		\
			ft_strcmp.c			\
			ft_strncmp.c		\
			ft_atoi.c			\
			ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isascii.c		\
			ft_isprint.c		\
			ft_toupper.c		\
			ft_tolower.c		\
			ft_memalloc.c		\
			ft_memdel.c			\
			ft_strnew.c			\
			ft_strdel.c			\
			ft_strclr.c			\
			ft_striter.c		\
			ft_striteri.c		\
			ft_strmap.c			\
			ft_strmapi.c		\
			ft_strequ.c			\
			ft_strnequ.c		\
			ft_strsub.c			\
			ft_strjoin.c		\
			ft_strjoin_slash.c	\
			ft_strtrim.c		\
			ft_strsplit.c		\
			ft_strsplit_space.c	\
			ft_itoa.c			\
			ft_putchar.c		\
			ft_putstr.c			\
			ft_putendl.c		\
			ft_putnbr.c			\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_lstnew.c			\
			ft_lstdelone.c		\
			ft_lstdel.c			\
			ft_lstadd.c			\
			ft_lstiter.c		\
			ft_lstmap.c			\
			ft_abs.c			\
			ft_premiere.c		\
			ft_lstend.c			\
			ft_lstlen.c			\
			ft_memalloc_td.c	\
			ft_free_td.c		\
			ft_isspace.c		\
			ft_error.c			\
			get_next_line.c		\

OBJ_NAME	=		$(SRC:.c=.o)
OBJ_PATH	=		obj/
OBJ			=		$(addprefix $(OBJ_PATH), $(OBJ_NAME))
NAME		=		libft.a
FLAGS		=		-Wall -Wextra -Werror

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all: $(NAME)

$(OBJ_PATH)%.o: %.c
	@mkdir -p obj
	gcc -c $(FLAGS) -I includes $< -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean:	clean
	rm -rf $(NAME)

re: fclean $(NAME)
