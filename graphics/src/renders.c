/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:02:23 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/08 08:21:41 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_line(t_game *game, double x, double y, double dir, int side, int i)
{
	double	dist2wall;
	double	line_size;
	int		j;
	double	integer;
	double	decimal;
	double	delta_x;
	double	delta_y;

	dist2wall = 0;
	if (side == 0)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			decimal = modf(x, &integer);
			decimal = 1 - decimal;
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_x = decimal / cos(dir);
			decimal = modf(y, &integer);
			decimal = 1 - decimal;
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_y = decimal / sin(dir);
			if (delta_x < delta_y)
			{
				x += delta_x * cos(dir);
				y += delta_x * sin(dir);
				dist2wall += delta_x;
				if (game->map.map[(int)(x + 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x += delta_y * cos(dir);
				y += delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map.map[(int)x][(int)(y + 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 1)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			decimal = modf(x, &integer);
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_x = decimal / cos(dir);
			decimal = modf(y, &integer);
			decimal = 1 - decimal;
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_y = decimal / sin(dir);
			if (delta_x < delta_y)
			{
				x -= delta_x * cos(dir);
				y += delta_x * sin(dir);
				dist2wall += delta_x;
				if (game->map.map[(int)(x - 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x -= delta_y * cos(dir);
				y += delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map.map[(int)x][(int)(y + 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 2)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			decimal = modf(x, &integer);
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_x = decimal / cos(dir);
			decimal = modf(y, &integer);
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_y = decimal / sin(dir);
			if (delta_x < delta_y)
			{
				x -= delta_x * cos(dir);
				y -= delta_x * sin(dir);
				dist2wall += delta_x;
				if (game->map.map[(int)(x - 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x -= delta_y * cos(dir);
				y -= delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map.map[(int)x][(int)(y - 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 3)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			decimal = modf(x, &integer);
			decimal = 1 - decimal;
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_x = decimal / cos(dir);
			decimal = modf(y, &integer);
			if (decimal == 0)
				decimal = 0.9999999999999999;
			delta_y = decimal / sin(dir);
			if (delta_x < delta_y)
			{
				x += delta_x * cos(dir);
				y -= delta_x * sin(dir);
				dist2wall += delta_x;
				if (game->map.map[(int)(x + 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x += delta_y * cos(dir);
				y -= delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map.map[(int)x][(int)(y - 0.0001)] == '1')
					break ;
			}
		}
	}
	line_size = 1 / dist2wall * 600 * (45.0 / 70.0);
	if (line_size > 600)
		line_size = 600;
	j = 0;
	while (j < line_size)
	{
		my_pixel_put(&game->graphics.img, i, j + 300 - line_size / 2, 0x00FFFFFF);
		j++;
	}
}

void	cube_render(t_game *game)
{
	int		i;
	double	dir;
	int		side;

	i = 0;
	dir = game->player.dir;
	side = game->player.side;
	while (i < 400)
	{
		if (side == 0)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 1;
			}
		}
		else if (side == 1)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 2;
			}
		}
		else if (side == 2)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 3;
			}
		}
		else if (side == 3)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 0;
			}
		}
		i++;
	}
	i = 0;
	while (i < 800)
	{
		if (side == 0)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 3;
			}
		}
		else if (side == 1)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 0;
			}
		}
		else if (side == 2)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 1;
			}
		}
		else if (side == 3)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 2;
			}
		}
		put_line(game, game->player.x, game->player.y, dir, side, i);
		i++;
	}
}

int	minimaprender(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == '1')
			{
				k = 0;
				while (k < 10)
				{
					l = 0;
					while (l < 10)
					{
						my_pixel_put(&game->graphics.img, j * 10 + k, i * 10 + l, 0x00FFFFFF);
						l++;
					}
					k++;
				}
			}
			else if (game->map.map[i][j] == '0' || game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' || game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				k = 0;
				while (k < 10)
				{
					l = 0;
					while (l < 10)
					{
						my_pixel_put(&game->graphics.img, j * 10 + k, i * 10 + l, 0x00000000);
						l++;
					}
					k++;
				}
			}
			else if (game->map.map[i][j] == ' ')
			{
				k = 0;
				while (k < 10)
				{
					l = 0;
					while (l < 10)
					{
						my_pixel_put(&game->graphics.img, j * 10 + k, i * 10 + l, 0x00FF0000);
						l++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
	playerrender(game);
	return (1);
}

void	playerrender(t_game *game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = (int) game->player.x;
	y = (int) game->player.y;
	i = ((int)(game->player.x * 10)) % 10;
	j = ((int)(game->player.y * 10)) % 10;
	my_pixel_put(&game->graphics.img, y * 10 + j, x * 10 + i, 0x00FFFFFF);
}

int	map_render(t_game *game)
{
	int			i;
	int			j;

	i = -1;
	while (++i < 800)
	{
		j = -1;
		while (++j < 600)
		{
			if (j < 300)
				my_pixel_put(&game->graphics.img, i, j, 0x00FF0000);
			else
				my_pixel_put(&game->graphics.img, i, j, 0x0000FF00);
		}
	}
	return (1);
}
