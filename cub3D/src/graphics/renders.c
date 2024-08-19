/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:02:23 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/19 20:22:23 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_color(t_gs *game, double x, double y, double z, int vars.orientation)
{
	int		color;
	double	vars.integer;
	double	vars.decimal;

	(void)z;
	if (vars.orientation == 0)
	{
		vars.decimal = modf(y, &vars.integer);
		color = (*(int *)(game->graphics.no.addr + (game->graphics.no.width * ((int)(game->graphics.no.height * z)) + ((int)(game->graphics.no.width * vars.decimal))) * game->graphics.no.bits_per_pixel / 8));
	}
	else if (vars.orientation == 1)
	{
		vars.decimal = modf(y, &vars.integer);
		color = (*(int *)(game->graphics.so.addr + (game->graphics.so.width * ((int)(game->graphics.so.height * z)) + ((int)(game->graphics.so.width * (1 - vars.decimal)))) * game->graphics.so.bits_per_pixel / 8));
	}
	else if (vars.orientation == 2)
	{
		vars.decimal = modf(x, &vars.integer);
		color = (*(int *)(game->graphics.we.addr + (game->graphics.we.width * ((int)(game->graphics.we.height * z)) + ((int)(game->graphics.we.width * (1 - vars.decimal)))) * game->graphics.we.bits_per_pixel / 8));
	}
	else if (vars.orientation == 3)
	{
		vars.decimal = modf(x, &vars.integer);
		color = (*(int *)(game->graphics.ea.addr + (game->graphics.ea.width * ((int)(game->graphics.ea.height * z)) + ((int)(game->graphics.ea.width * (1 - vars.decimal)))) * game->graphics.ea.bits_per_pixel / 8));
	}
	else
	{
		color = 0x00000000;
	}
	return (color);
}

void	put_line(t_gs *game, double x, double y, double dir, int side, int i)
{
	t_putline	vars;

	vars.orientation = 0;
	vars.dist2wall = 0;
	vars.perp_dir = game->player.dir;
	vars.perp_side = game->player.side;
	vars.perp_dir += M_PI_2;
	vars.perp_dir = M_PI_2 - vars.perp_dir + M_PI_2;
	if (vars.perp_side == 2)
		vars.perp_side = 0;
	if (vars.perp_side == 3)
		vars.perp_side = 1;
	if (vars.perp_side == 0)
		vars.perp_side = 1;
	else if (vars.perp_side == 1)
		vars.perp_side = 0;
/*	if (vars.perp_side == 0)
		vars.perp_dir = vars.perp_dir + M_PI_2;*/
	if (vars.perp_side == 1)
		vars.perp_dir = M_PI_2 - vars.perp_dir + M_PI_2;
	vars.perp_slope = tan(vars.perp_dir);
	if (vars.perp_slope > 1000 || vars.perp_slope < -1000)
		vars.perp_slope = 1000;
	vars.perp_oo = -vars.perp_slope * x + y;
	if (side == 0)
	{
		while (game->map[(int)x][(int)y] != '1')
		{
			vars.decimal = modf(x, &vars.integer);
			vars.decimal = 1 - vars.decimal;
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltax = vars.decimal / cos(dir);
			vars.decimal = modf(y, &vars.integer);
			vars.decimal = 1 - vars.decimal;
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltay = vars.decimal / sin(dir);
			if (vars.deltax < vars.deltay)
			{
				x += vars.deltax * cos(dir);
				y += vars.deltax * sin(dir);
				vars.dist2wall += vars.deltax;
				if (game->map[(int)(x + 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x += vars.deltay * cos(dir);
				y += vars.deltay * sin(dir);
				vars.dist2wall += vars.deltay;
				if (game->map[(int)x][(int)(y + 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 1)
	{
		while (game->map[(int)x][(int)y] != '1')
		{
			vars.decimal = modf(x, &vars.integer);
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltax = vars.decimal / cos(dir);
			vars.decimal = modf(y, &vars.integer);
			vars.decimal = 1 - vars.decimal;
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltay = vars.decimal / sin(dir);
			if (vars.deltax < vars.deltay)
			{
				x -= vars.deltax * cos(dir);
				y += vars.deltax * sin(dir);
				vars.dist2wall += vars.deltax;
				if (game->map[(int)(x - 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x -= vars.deltay * cos(dir);
				y += vars.deltay * sin(dir);
				vars.dist2wall += vars.deltay;
				if (game->map[(int)x][(int)(y + 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 2)
	{
		while (game->map[(int)x][(int)y] != '1')
		{
			vars.decimal = modf(x, &vars.integer);
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltax = vars.decimal / cos(dir);
			vars.decimal = modf(y, &vars.integer);
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltay = vars.decimal / sin(dir);
			if (vars.deltax < vars.deltay)
			{
				x -= vars.deltax * cos(dir);
				y -= vars.deltax * sin(dir);
				vars.dist2wall += vars.deltax;
				if (game->map[(int)(x - 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x -= vars.deltay * cos(dir);
				y -= vars.deltay * sin(dir);
				vars.dist2wall += vars.deltay;
				if (game->map[(int)x][(int)(y - 0.0001)] == '1')
					break ;
			}
		}
	}
	else if (side == 3)
	{
		while (game->map[(int)x][(int)y] != '1')
		{
			vars.decimal = modf(x, &vars.integer);
			vars.decimal = 1 - vars.decimal;
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltax = vars.decimal / cos(dir);
			vars.decimal = modf(y, &vars.integer);
			if (vars.decimal == 0)
				vars.decimal = 0.9999999999999999;
			vars.deltay = vars.decimal / sin(dir);
			if (vars.deltax < vars.deltay)
			{
				x += vars.deltax * cos(dir);
				y -= vars.deltax * sin(dir);
				vars.dist2wall += vars.deltax;
				if (game->map[(int)(x + 0.0001)][(int)y] == '1')
					break ;
			}
			else
			{
				x += vars.deltay * cos(dir);
				y -= vars.deltay * sin(dir);
				vars.dist2wall += vars.deltay;
				if (game->map[(int)x][(int)(y - 0.0001)] == '1')
					break ;
			}
		}
	}
	vars.paralel_dir = game->player.dir;
	parallel_side = game->player.side;
	if (parallel_side == 2)
		parallel_side = 0;
	if (parallel_side == 3)
		parallel_side = 1;
/*	if (parallel_side == 0)
		vars.paralel_dir = vars.paralel_dir + M_PI_2;*/
	if (parallel_side == 1)
		vars.paralel_dir = M_PI_2 - vars.paralel_dir + M_PI_2;
	vars.paralel_slope = tan(vars.paralel_dir);
	if (vars.paralel_slope > 1000 || vars.paralel_slope < -1000)
		vars.paralel_slope = 1000;
	vars.paralel_oo = -vars.paralel_slope * x + y;
	vars.intercept_x = (vars.paralel_oo - vars.perp_oo) / (vars.perp_slope - vars.paralel_slope);
	vars.intercept_y = vars.perp_slope * vars.intercept_x + vars.perp_oo;
	vars.dist2wall = sqrt(pow(vars.intercept_x - x, 2) + pow(vars.intercept_y - y, 2));
	vars.line_size = 1 / vars.dist2wall * 600;
	if (side == 0)
	{
		vars.decimal = modf(x, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 1;
		vars.decimal = modf(y, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 3;
	}
	else if (side == 1)
	{
		vars.decimal = modf(x, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 0;
		vars.decimal = modf(y, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 3;
	}
	else if (side == 2)
	{
		vars.decimal = modf(x, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 0;
		vars.decimal = modf(y, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 2;
	}
	else if (side == 3)
	{
		vars.decimal = modf(x, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 1;
		vars.decimal = modf(y, &vars.integer);
		if (vars.decimal > -0.0001 && vars.decimal < 0.0001)
			vars.orientation = 2;
	}
	j = 0;
	while (j < vars.line_size)
	{
		if ((j > (vars.line_size - 600) / 2) && j < vars.line_size - (vars.line_size - 600) / 2)
			my_pixel_put(&game->graphics.img, i, j + 300 - vars.line_size / 2, get_color(game, x, y, (double)j / (double)vars.line_size, vars.orientation));
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
