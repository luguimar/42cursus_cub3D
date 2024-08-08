/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:46:50 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/08 01:09:20 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include <math.h>

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

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
	int		side;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_graphics
{
	void	*mlx;
	void	*win;
	t_img	img;
	int		floor[3];
	int		ceiling[3];
	char	*no_t;
	char	*so_t;
	char	*ea_t;
	char	*we_t;
}	t_graphics;

typedef struct s_map
{
	int		width;
	int		height;
	char	**map;
}	t_map;

typedef struct s_game
{
	t_graphics	graphics;
	t_map		map;
	t_player	player;
}	t_game;

int		move(int keycode, t_game *game);
int		key_hook(int keycode, t_game *game);
int		map_render(t_game *game);
void	playerrender(t_game *game);
int		minimaprender(t_game *game);
void	put_line(t_game *game, double x, double y, double dir, int side, int i);
void	cube_render(t_game *game);
double	get_dir(char c);
int		get_side(char c);
void	get_player_dir(t_game *game);
void	get_player_position(t_game *game);
int		mlx_close(t_game *game);
void	my_pixel_put(t_img *img, int x, int y, int color);
int		error_msg(char *msg, int ret);

#endif
