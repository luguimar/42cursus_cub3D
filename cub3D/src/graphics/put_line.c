/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 02:42:33 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/22 02:55:48 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_line_aux_extra(int side, t_putline *vars)
{
	if (side == 2)
	{
		vars->decimal = modf(vars->x, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 0;
		vars->decimal = modf(vars->y, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 2;
	}
	else if (side == 3)
	{
		vars->decimal = modf(vars->x, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 1;
		vars->decimal = modf(vars->y, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 2;
	}
}

void	put_line_aux(int side, t_putline *vars)
{
	if (side == 0)
	{
		vars->decimal = modf(vars->x, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 1;
		vars->decimal = modf(vars->y, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 3;
	}
	else if (side == 1)
	{
		vars->decimal = modf(vars->x, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 0;
		vars->decimal = modf(vars->y, &vars->integer);
		if (vars->decimal > -0.0001 && vars->decimal < 0.0001)
			vars->orientation = 3;
	}
	else
		put_line_aux_extra(side, vars);
}

void	put_line(t_gs *game, double dir, int side, int i)
{
	t_putline	vars;

	vars_init(&vars, game);
	if (side == 0)
		put_line_side0(game, &vars, dir);
	else if (side == 1)
		put_line_side1(game, &vars, dir);
	else if (side == 2)
		put_line_side2(game, &vars, dir);
	else if (side == 3)
		put_line_side3(game, &vars, dir);
	vars_init2(&vars, game);
	put_line_aux(side, &vars);
	vars.j = 0;
	while (vars.j < vars.line_size)
	{
		if ((vars.j > (vars.line_size - 600) / 2) && vars.j \
		< vars.line_size - (vars.line_size - 600) / 2)
			my_pixel_put(&game->graphics.img, i, vars.j + 300 - \
				vars.line_size / 2, get_color(game, vars, \
				(double)vars.j / (double)vars.line_size));
		vars.j++;
	}
}
