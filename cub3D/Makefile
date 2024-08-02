# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/10 22:33:22 by luguimar          #+#    #+#              #
#    Updated: 2024/07/25 02:35:43 by luguimar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = src/parser/main.c src/parser/parse.c src/parser/checker.c src/parser/map_parse.c src/parser/parse_utils.c src/graphics/graphics.c

OBJS = ${SRC:.c=.o}

CC = cc -g
MOVE = mv
REMOVE = rm -f
EXTRACT = tar -xvf
DOWNLOAD = wget -O
CFLAGS = -Wall -Wextra -Werror -O3
INCLUDE = -I .
MAKE = make -C
LIBRARIES = lib
MINILIBX_FILE = minilibx-linux.tgz
MINILIBX_URL = https://cdn.intra.42.fr/document/document/25858/minilibx-linux.tgz
LIBFT_PATH = lib/libft
MLX_PATH = lib/mlx
LIBFT = ${LIBFT_PATH}/libft.a
MLX = -L ${MLX_PATH} -lmlx -Ilmlx -lXext -lX11 -lm

$(NAME): $(MLX) ${OBJS} ${LIBFT}
		${CC} ${OBJS} ${LIBFT} ${MLX} -o ${NAME}

$(LIBFT):
		${MAKE} ${LIBFT_PATH}

$(MLX): download-and-extract-mlx
		${MAKE} ${MLX_PATH}

download-and-extract-mlx:
		if [ ! -d "${MLX_PATH}" ]; then \
		${DOWNLOAD} ${MINILIBX_FILE} ${MINILIBX_URL}; \
		${EXTRACT} ${MINILIBX_FILE} -C ${LIBRARIES}; \
		${REMOVE} ${MINILIBX_FILE}; \
		${MOVE} lib/minilibx-linux ${MLX_PATH}; \
		fi

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

.PHONY: download-and-extract-mlx all clean fclean re
