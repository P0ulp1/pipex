# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phautena <phautena@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 12:24:27 by phautena          #+#    #+#              #
#    Updated: 2024/09/30 16:35:24 by phautena         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = ./srcs/pipex.c ./srcs/cmd.c ./srcs/free.c ./srcs/list.c ./srcs/utils.c ./srcs/env.c ./srcs/exec.c ./srcs/here_doc.c

CC = cc -Wall -Werror -Wextra -ggdb -g -I./includes/

OBJ = ${SRC:.c=.o}

LIBFT_ARCHIVE = ./Libft/libft.a

PRINTF_ARCHIVE = ./ft_printf/libftprintf.a

GNL_ARCHIVE = ./GNL/gnl.a

.c.o:
	${CC} -c $< -o $@

all: ${NAME}

${NAME}: ${LIBFT_ARCHIVE} ${PRINTF_ARCHIVE} ${GNL_ARCHIVE} ${OBJ}
	${CC} ${OBJ} ${LIBFT_ARCHIVE} ${PRINTF_ARCHIVE} ${GNL_ARCHIVE} -o ${NAME}

${LIBFT_ARCHIVE}:
	make -sC ./Libft

${PRINTF_ARCHIVE}:
	make -sC ./ft_printf

${GNL_ARCHIVE}:
	make -sC ./GNL

clean:
	make clean -sC ./Libft
	make clean -sC ./ft_printf
	make clean -sC ./GNL
	rm -f ${OBJ}

fclean: clean
	make fclean -sC ./Libft
	make fclean -sC ./ft_printf
	make fclean -sC ./GNL
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
