/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:02:23 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/22 02:46:34 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_color_extra(t_gs *game, t_putline vars, double z)
{
	int		color;

	if (vars.orientation == 2)
	{
		vars.decimal = modf(vars.x, &vars.integer);
		color = (*(int *)(game->graphics.we.addr + (game->graphics.we.width * \
			((int)(game->graphics.we.height * z)) + \
			((int)(game->graphics.we.width * (1 - vars.decimal)))) * \
			game->graphics.we.bits_per_pixel / 8));
	}
	else if (vars.orientation == 3)
	{
		vars.decimal = modf(vars.x, &vars.integer);
		color = (*(int *)(game->graphics.ea.addr + (game->graphics.ea.width * \
			((int)(game->graphics.ea.height * z)) + \
			((int)(game->graphics.ea.width * (1 - vars.decimal)))) * \
			game->graphics.ea.bits_per_pixel / 8));
	}
	else
		color = 0x00000000;
	return (color);
}

int	get_color(t_gs *game, t_putline vars, double z)
{
	int		color;

	if (vars.orientation == 0)
	{
		vars.decimal = modf(vars.y, &vars.integer);
		color = (*(int *)(game->graphics.no.addr + (game->graphics.no.width \
			* ((int)(game->graphics.no.height * z)) + \
			((int)(game->graphics.no.width * vars.decimal))) * \
			game->graphics.no.bits_per_pixel / 8));
	}
	else if (vars.orientation == 1)
	{
		vars.decimal = modf(vars.y, &vars.integer);
		color = (*(int *)(game->graphics.so.addr + (game->graphics.so.width \
			* ((int)(game->graphics.so.height * z)) + \
			((int)(game->graphics.so.width * (1 - vars.decimal)))) \
			* game->graphics.so.bits_per_pixel / 8));
	}
	else
		color = get_color_extra(game, vars, z);
	return (color);
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
				my_pixel_put(&game->graphics.img, i, j, \
					rgbtohex(game->ceiling));
			else
				my_pixel_put(&game->graphics.img, i, j, rgbtohex(game->floor));
		}
	}
	return (1);
}
