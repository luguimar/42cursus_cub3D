/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line_case_sides.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 02:47:45 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/22 02:54:13 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	vars_init(t_putline *vars, t_gs *game)
{
	vars->x = game->player.x;
	vars->y = game->player.y;
	vars->orientation = 0;
	vars->dist2wall = 0;
	vars->perp_dir = game->player.dir;
	vars->perp_side = game->player.side;
	vars->perp_dir += M_PI_2;
	vars->perp_dir = M_PI_2 - vars->perp_dir + M_PI_2;
	if (vars->perp_side == 2)
		vars->perp_side = 0;
	if (vars->perp_side == 3)
		vars->perp_side = 1;
	if (vars->perp_side == 0)
		vars->perp_side = 1;
	else if (vars->perp_side == 1)
		vars->perp_side = 0;
	if (vars->perp_side == 1)
		vars->perp_dir = M_PI_2 - vars->perp_dir + M_PI_2;
	vars->perp_slope = tan(vars->perp_dir);
	if (vars->perp_slope > 1000 || vars->perp_slope < -1000)
		vars->perp_slope = 1000;
	vars->perp_oo = -vars->perp_slope * vars->x + vars->y;
}

void	vars_init2(t_putline *vars, t_gs *game)
{
	vars->parallel_dir = game->player.dir;
	vars->parallel_side = game->player.side;
	if (vars->parallel_side == 2)
		vars->parallel_side = 0;
	if (vars->parallel_side == 3)
		vars->parallel_side = 1;
	if (vars->parallel_side == 1)
		vars->parallel_dir = M_PI_2 - vars->parallel_dir + M_PI_2;
	vars->parallel_slope = tan(vars->parallel_dir);
	if (vars->parallel_slope > 1000 || vars->parallel_slope < -1000)
		vars->parallel_slope = 1000;
	vars->parallel_oo = -vars->parallel_slope * vars->x + vars->y;
	vars->intercept_x = (vars->parallel_oo - vars->perp_oo) / \
		(vars->perp_slope - vars->parallel_slope);
	vars->intercept_y = vars->perp_slope * vars->intercept_x + vars->perp_oo;
	vars->dist2wall = sqrt(pow(vars->intercept_x - vars->x, 2) + \
		pow(vars->intercept_y - vars->y, 2));
	vars->line_size = 1 / vars->dist2wall * 600;
}

void	put_line_side0_aux(t_putline *vars, double dir)
{
	vars->decimal = modf(vars->x, &vars->integer);
	vars->decimal = 1 - vars->decimal;
	if (vars->decimal == 0)
		vars->decimal = 0.9999999999999999;
	vars->delta_x = vars->decimal / cos(dir);
	vars->decimal = modf(vars->y, &vars->integer);
	vars->decimal = 1 - vars->decimal;
}

void	put_line_side0(t_gs *game, t_putline *vars, double dir)
{
	while (game->map[(int)vars->x][(int)vars->y] != '1')
	{
		put_line_side0_aux(vars, dir);
		if (vars->decimal == 0)
			vars->decimal = 0.9999999999999999;
		vars->delta_y = vars->decimal / sin(dir);
		if (vars->delta_x < vars->delta_y)
		{
			vars->x += vars->delta_x * cos(dir);
			vars->y += vars->delta_x * sin(dir);
			vars->dist2wall += vars->delta_x;
			if (game->map[(int)(vars->x + 0.0001)][(int)vars->y] == '1')
				break ;
		}
		else
		{
			vars->x += vars->delta_y * cos(dir);
			vars->y += vars->delta_y * sin(dir);
			vars->dist2wall += vars->delta_y;
			if (game->map[(int)vars->x][(int)(vars->y + 0.0001)] == '1')
				break ;
		}
	}
}

void	put_line_side1_aux(t_putline *vars, double dir)
{
	vars->decimal = modf(vars->x, &vars->integer);
	if (vars->decimal == 0)
		vars->decimal = 0.9999999999999999;
	vars->delta_x = vars->decimal / cos(dir);
	vars->decimal = modf(vars->y, &vars->integer);
	vars->decimal = 1 - vars->decimal;
	if (vars->decimal == 0)
		vars->decimal = 0.9999999999999999;
}
