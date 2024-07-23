/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:45 by jduraes-          #+#    #+#             */
/*   Updated: 2024/07/23 20:24:53 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "libft/libft.h"

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct	s_gs
{
	char	**raw;
	char	**map;
	int        xlen;
	int        ylen;
	int	floor[3];
	int	ceiling[3];
	char	*no_t;
	char	*so_t;
	char	*ea_t;
	char	*we_t;
	t_position	*player;
}				t_gs;

int	parser(char *f, t_gs *gs);
int	checker(t_gs *gs);
int	flood_fill(t_gs *gs, int x, int y, char **map);
void    ft_perror(char *str, int fd);

#endif
