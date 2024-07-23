# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/15 20:48:16 by jduraes-          #+#    #+#              #
#    Updated: 2024/07/18 17:29:54 by jduraes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC = src/main.c src/parse.c src/checker.c
OBJS = $(SRC:.c=.o)
HEADER = cub3d.h
CC = cc -g
RM = rm -f
INCLUDE = -I .
CFLAGS = -Wall -Wextra -Werror
#IFLAGS = -L ./minilibx-linux -lmlx -Ilmlx -lXext -lX11 -lm
#LIBMLX = minilibx-linux/libmlx.a

.o:.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	make bonus -C libft all
	$(CC) $(OBJS) -L libft -lft -o $(NAME)

all: $(NAME)
clean:
	$(RM) $(OBJS)
	@make clean -C libft

fclean:	clean
	$(RM) $(NAME)
	@make fclean -C libft

re: fclean all
	make re -C libft

.phony: clean fclean re
