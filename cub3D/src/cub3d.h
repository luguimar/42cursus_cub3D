/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:45 by jduraes-          #+#    #+#             */
/*   Updated: 2024/08/02 19:30:45 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include "../lib/mlx/mlx.h"
#include "../lib/libft/libft.h"

typedef enum e_key
{
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	ESC = 65307,
	LEFT = 65361,
	RIGHT = 65363,
}	t_key;

typedef struct s_position
{
	int			x;
	int			y;
}				t_position;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	int		floor[3];
	int		ceiling[3];
	char	*no_t;
	char	*so_t;
	char	*ea_t;
	char	*we_t;
}	t_graphics;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	int		side;
}	t_player;

typedef struct	s_gs
{
	char	**raw;
	char	**map;
	int		xlen;
	int		ylen;
	int		tl;
	int	floor[3];
	int	ceiling[3];
	char	*no_t;
	char	*so_t;
	char	*ea_t;
	char	*we_t;
	t_position	*playerp;
	t_graphics	graphics;
	t_player	player;
}				t_gs;

int	parser(char *f, t_gs *gs);
int	checker(t_gs *gs);
void    ft_perror(char *str, int fd);
void	runitdown(int fd, char *line);
int	check_info(t_gs *gs);
int	copyconvert(char **s, int *a);
int	t_access(char *s, char **d);
int	map_start(int fd, t_gs *gs, char *f);
unsigned int	rgbtohex(int *rgb);
void	mlx_start(t_gs *game);

#endif
