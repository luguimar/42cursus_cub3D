/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line_case_sides1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 02:48:34 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/22 02:54:41 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_line_side1(t_gs *game, t_putline *vars, double dir)
{
	while (game->map[(int)vars->x][(int)vars->y] != '1')
	{
		put_line_side1_aux(vars, dir);
		vars->delta_y = vars->decimal / sin(dir);
		if (vars->delta_x < vars->delta_y)
		{
			vars->x -= vars->delta_x * cos(dir);
			vars->y += vars->delta_x * sin(dir);
			vars->dist2wall += vars->delta_x;
			if (game->map[(int)(vars->x - 0.0001)][(int)vars->y] == '1')
				break ;
		}
		else
		{
			vars->x -= vars->delta_y * cos(dir);
			vars->y += vars->delta_y * sin(dir);
			vars->dist2wall += vars->delta_y;
			if (game->map[(int)vars->x][(int)(vars->y + 0.0001)] == '1')
				break ;
		}
	}
}

void	put_line_side2_aux(t_putline *vars, double dir)
{
	vars->decimal = modf(vars->x, &vars->integer);
	if (vars->decimal == 0)
		vars->decimal = 0.9999999999999999;
	vars->delta_x = vars->decimal / cos(dir);
	vars->decimal = modf(vars->y, &vars->integer);
	if (vars->decimal == 0)
		vars->decimal = 0.9999999999999999;
	vars->delta_y = vars->decimal / sin(dir);
}

void	put_line_side2(t_gs *game, t_putline *vars, double dir)
{
	while (game->map[(int)vars->x][(int)vars->y] != '1')
	{
		put_line_side2_aux(vars, dir);
		if (vars->delta_x < vars->delta_y)
		{
			vars->x -= vars->delta_x * cos(dir);
			vars->y -= vars->delta_x * sin(dir);
			vars->dist2wall += vars->delta_x;
			if (game->map[(int)(vars->x - 0.0001)][(int)vars->y] == '1')
				break ;
		}
		else
		{
			vars->x -= vars->delta_y * cos(dir);
			vars->y -= vars->delta_y * sin(dir);
			vars->dist2wall += vars->delta_y;
			if (game->map[(int)vars->x][(int)(vars->y - 0.0001)] == '1')
				break ;
		}
	}
}

void	put_line_side3_aux(t_putline *vars, double dir)
{
	vars->decimal = modf(vars->x, &vars->integer);
	vars->decimal = 1 - vars->decimal;
	if (vars->decimal == 0)
		vars->decimal = 0.9999999999999999;
	vars->delta_x = vars->decimal / cos(dir);
	vars->decimal = modf(vars->y, &vars->integer);
	if (vars->decimal == 0)
		vars->decimal = 0.9999999999999999;
	vars->delta_y = vars->decimal / sin(dir);
}

void	put_line_side3(t_gs *game, t_putline *vars, double dir)
{
	while (game->map[(int)vars->x][(int)vars->y] != '1')
	{
		put_line_side3_aux(vars, dir);
		if (vars->delta_x < vars->delta_y)
		{
			vars->x += vars->delta_x * cos(dir);
			vars->y -= vars->delta_x * sin(dir);
			vars->dist2wall += vars->delta_x;
			if (game->map[(int)(vars->x + 0.0001)][(int)vars->y] == '1')
				break ;
		}
		else
		{
			vars->x += vars->delta_y * cos(dir);
			vars->y -= vars->delta_y * sin(dir);
			vars->dist2wall += vars->delta_y;
			if (game->map[(int)vars->x][(int)(vars->y - 0.0001)] == '1')
				break ;
		}
	}
}
