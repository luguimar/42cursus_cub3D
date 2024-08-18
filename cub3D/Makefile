# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 22:33:22 by luguimar          #+#    #+#              #
#    Updated: 2024/08/18 20:18:30 by luguimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = src/parser/main.c src/parser/parse.c src/parser/checker.c src/parser/map_parse.c src/parser/parse_utils.c src/graphics/graphics.c src/graphics/moves.c src/graphics/positions.c src/graphics/renders.c

OBJS = ${SRC:.c=.o}

CC = cc -g #-fsanitize=address
MOVE = mv
REMOVE = rm -f
EXTRACT = tar -xvf
DOWNLOAD = wget -O
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I .
MAKE = make -C
LIBRARIES = lib
MINILIBX_FILE = minilibx-linux.tgz
MINILIBX_URL = https://cdn.intra.42.fr/document/document/25858/minilibx-linux.tgz
LIBFT_PATH = lib/libft
MLX_PATH = lib/mlx
LIBFT = ${LIBFT_PATH}/libft.a
MLX_FILE = ${MLX_PATH}/libmlx.a
MLX = -L ${MLX_PATH} -lmlx -Ilmlx -lXext -lX11 -lm

$(NAME): ${MLX_FILE} ${OBJS} ${LIBFT}
		${CC} ${OBJS} ${LIBFT} ${MLX} -o ${NAME}

$(LIBFT):
		${MAKE} ${LIBFT_PATH}

${MLX_FILE}:
		if [ ! -d "${MLX_PATH}" ]; then \
		${DOWNLOAD} ${MINILIBX_FILE} ${MINILIBX_URL}; \
		${EXTRACT} ${MINILIBX_FILE} -C ${LIBRARIES}; \
		${REMOVE} ${MINILIBX_FILE}; \
		${MOVE} lib/minilibx-linux ${MLX_PATH}; \
		fi
		${MAKE} ${MLX_PATH}
		
all: ${NAME}

clean:
		${MAKE} ${LIBFT_PATH} clean
		if [ -d "${MLX_PATH}" ]; then ${MAKE} ${MLX_PATH} clean; fi
		${RM} ${OBJS}

fclean: clean
		${MAKE} ${LIBFT_PATH} fclean
		if [ -d "${MLX_PATH}" ]; then ${RM} -r ${MLX_PATH}; fi
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
