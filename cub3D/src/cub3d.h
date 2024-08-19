/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:01:45 by jduraes-          #+#    #+#             */
/*   Updated: 2024/08/19 20:22:07 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <math.h>
# include "../lib/mlx/mlx.h"
# include "../lib/libft/libft.h"

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

typedef struct s_putline
{
	double	dist2wall;
	double	line_size;
	int		j;
	int		orientation;
	double	integer;
	double	decimal;
	double	delta_x;
	double	delta_y;
	double	perp_dir;
	double	perp_slope;
	double	perp_side;
	double	perp_oo;
	double	parallel_dir;
	double	parallel_slope;
	double	parallel_side;
	double	parallel_oo;
	double	intercept_x;
	double	intercept_y;
}	t_putline;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		height;
	int		width;
	int		endian;
}	t_img;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_img	no;
	t_img	so;
	t_img	ea;
	t_img	we;
	int		floor[3];
	int		ceiling[3];
}	t_graphics;

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	int		side;
}	t_player;

typedef struct s_gs
{
	char		**raw;
	char		**map;
	int			xlen;
	int			ylen;
	int			tl;
	int			floor[3];
	int			ceiling[3];
	char		*no_t;
	char		*so_t;
	char		*ea_t;
	char		*we_t;
	t_position	*playerp;
	t_graphics	graphics;
	t_player	player;
}				t_gs;

int				parser(char *f, t_gs *gs);
int				checker(t_gs *gs);
void			ft_perror(char *str, int fd);
void			runitdown(int fd, char *line);
int				check_info(t_gs *gs);
int				copyconvert(char **s, int *a);
int				t_access(char *s, char **d);
int				map_start(int fd, t_gs *gs, char *f);
unsigned int	rgbtohex(int *rgb);
void			mlx_start(t_gs *game);
void			deinitialize(t_gs *gs);

int				move(int keycode, t_gs *game);
int				key_hook(int keycode, t_gs *game);
int				map_render(t_gs *game);
void			playerrender(t_gs *game);
int				minimaprender(t_gs *game);
void			put_line(t_gs *game, double x, double y, double dir, int side, int i);
void			cube_render(t_gs *game);
double			get_dir(char c);
int				get_side(char c);
void			get_player_dir(t_gs *game);
void			get_player_position(t_gs *game);
int				mlx_close(t_gs *game);
void			my_pixel_put(t_img *img, int x, int y, int color);
int				error_msg(char *msg, int ret);

#endif
