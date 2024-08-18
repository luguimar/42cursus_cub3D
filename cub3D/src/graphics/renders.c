/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:02:23 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/16 02:02:00 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_color(t_gs *game, double x, double y, double z, int orientation)
{
	int		color;
	double	integer;
	double	decimal;

	(void)z;
	if (orientation == 0)
	{
		decimal = modf(y, &integer);
		color = (*(int *)(game->graphics.no.addr + (game->graphics.no.width * ((int)(game->graphics.no.height * z)) + ((int)(game->graphics.no.width * decimal))) * game->graphics.no.bits_per_pixel / 8));
	}
	else if (orientation == 1)
	{
		decimal = modf(y, &integer);
		color = (*(int *)(game->graphics.so.addr + (game->graphics.so.width * ((int)(game->graphics.so.height * z)) + ((int)(game->graphics.so.width * (1 - decimal)))) * game->graphics.so.bits_per_pixel / 8));
	}
	else if (orientation == 2)
	{
		decimal = modf(x, &integer);
		color = (*(int *)(game->graphics.we.addr + (game->graphics.we.width * ((int)(game->graphics.we.height * z)) + ((int)(game->graphics.we.width * (1 - decimal)))) * game->graphics.we.bits_per_pixel / 8));
	}
	else if (orientation == 3)
	{
		decimal = modf(x, &integer);
		color = (*(int *)(game->graphics.ea.addr + (game->graphics.ea.width * ((int)(game->graphics.ea.height * z)) + ((int)(game->graphics.ea.width * (1 - decimal)))) * game->graphics.ea.bits_per_pixel / 8));
	}
	else
	{
		color = 0x00000000;
	}
	return (color);
}

void	put_line(t_gs *game, double x, double y, double dir, int side, int i)
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

	dist2wall = 0;
	perp_dir = game->player.dir;
	perp_side = game->player.side;
	perp_dir += M_PI_2;
	perp_dir = M_PI_2 - perp_dir + M_PI_2;
	if (perp_side == 2)
		perp_side = 0;
	if (perp_side == 3)
		perp_side = 1;
	if (perp_side == 0)
		perp_side = 1;
	else if (perp_side == 1)
		perp_side = 0;
/*	if (perp_side == 0)
		perp_dir = perp_dir + M_PI_2;*/
	if (perp_side == 1)
		perp_dir = M_PI_2 - perp_dir + M_PI_2;
	perp_slope = tan(perp_dir);
	if (perp_slope > 1000 || perp_slope < -1000)
		perp_slope = 1000;
	perp_oo = -perp_slope * x + y;
	if (side == 0)
	{
		while (game->map[(int)x][(int)y] != '1')
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
				if (game->map[(int)(x + 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x += delta_y * cos(dir);
				y += delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map[(int)x][(int)(y + 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 1)
	{
		while (game->map[(int)x][(int)y] != '1')
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
				if (game->map[(int)(x - 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x -= delta_y * cos(dir);
				y += delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map[(int)x][(int)(y + 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 2)
	{
		while (game->map[(int)x][(int)y] != '1')
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
				if (game->map[(int)(x - 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x -= delta_y * cos(dir);
				y -= delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map[(int)x][(int)(y - 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 3)
	{
		while (game->map[(int)x][(int)y] != '1')
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
				if (game->map[(int)(x + 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x += delta_y * cos(dir);
				y -= delta_y * sin(dir);
				dist2wall += delta_y;
				if (game->map[(int)x][(int)(y - 0.0001)] == '1')
					break ;
			}
		}
	}
	parallel_dir = game->player.dir;
	parallel_side = game->player.side;
	if (parallel_side == 2)
		parallel_side = 0;
	if (parallel_side == 3)
		parallel_side = 1;
/*	if (parallel_side == 0)
		parallel_dir = parallel_dir + M_PI_2;*/
	if (parallel_side == 1)
		parallel_dir = M_PI_2 - parallel_dir + M_PI_2;
	parallel_slope = tan(parallel_dir);
	if (parallel_slope > 1000 || parallel_slope < -1000)
		parallel_slope = 1000;
	parallel_oo = -parallel_slope * x + y;
	intercept_x = (parallel_oo - perp_oo) / (perp_slope - parallel_slope);
	intercept_y = perp_slope * intercept_x + perp_oo;
	dist2wall = sqrt(pow(intercept_x - x, 2) + pow(intercept_y - y, 2));
	line_size = 1 / dist2wall * 600;
	if (side == 0)
	{
		decimal = modf(x, &integer);
		if (decimal == 0)
			orientation = 1;
		decimal = modf(y, &integer);
		if (decimal == 0)
			orientation = 3;
	}
	else if (side == 1)
	{
		decimal = modf(x, &integer);
		if (decimal == 0)
			orientation = 0;
		decimal = modf(y, &integer);
		if (decimal == 0)
			orientation = 3;
	}
	else if (side == 2)
	{
		decimal = modf(x, &integer);
		if (decimal == 0)
			orientation = 0;
		decimal = modf(y, &integer);
		if (decimal == 0)
			orientation = 2;
	}
	else if (side == 3)
	{
		decimal = modf(x, &integer);
		if (decimal == 0)
			orientation = 1;
		decimal = modf(y, &integer);
		if (decimal == 0)
			orientation = 2;
	}
	j = 0;
	while (j < line_size)
	{
		if ((j > (line_size - 600) / 2) && j < line_size - (line_size - 600) / 2)
			my_pixel_put(&game->graphics.img, i, j + 300 - line_size / 2, get_color(game, x, y, (double)j / (double)line_size, orientation));
		j++;
	}
}

void	cube_render(t_gs *game)
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

int	minimaprender(t_gs *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
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
			else if (game->map[i][j] == '0' || game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
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
			else if (game->map[i][j] == ' ')
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

void	playerrender(t_gs *game)
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

int	map_render(t_gs *game)
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
				my_pixel_put(&game->graphics.img, i, j, rgbtohex(game->ceiling));
			else
				my_pixel_put(&game->graphics.img, i, j, rgbtohex(game->floor));
		}
	}
	return (1);
}
