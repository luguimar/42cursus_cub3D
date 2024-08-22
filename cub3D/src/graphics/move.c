/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:16:38 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/20 22:25:49 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	keycode_s(t_gs *game, double *new_x, double *new_y)
{
	if (game->player.side == 0)
	{
		*new_x -= 0.1 * cos(game->player.dir);
		*new_y -= 0.1 * sin(game->player.dir);
	}
	else if (game->player.side == 1)
	{
		*new_x += 0.1 * cos(game->player.dir);
		*new_y -= 0.1 * sin(game->player.dir);
	}
	else if (game->player.side == 2)
	{
		*new_x += 0.1 * cos(game->player.dir);
		*new_y += 0.1 * sin(game->player.dir);
	}
	else if (game->player.side == 3)
	{
		*new_x -= 0.1 * cos(game->player.dir);
		*new_y += 0.1 * sin(game->player.dir);
	}
}

static void	keycode_w(t_gs *game, double *new_x, double *new_y)
{
	if (game->player.side == 0)
	{
		*new_x += 0.1 * cos(game->player.dir);
		*new_y += 0.1 * sin(game->player.dir);
	}
	else if (game->player.side == 1)
	{
		*new_x -= 0.1 * cos(game->player.dir);
		*new_y += 0.1 * sin(game->player.dir);
	}
	else if (game->player.side == 2)
	{
		*new_x -= 0.1 * cos(game->player.dir);
		*new_y -= 0.1 * sin(game->player.dir);
	}
	else if (game->player.side == 3)
	{
		*new_x += 0.1 * cos(game->player.dir);
		*new_y -= 0.1 * sin(game->player.dir);
	}
}

static void	keycode_a(t_gs *game, double *new_x, double *new_y)
{
	if (game->player.side == 0)
	{
		*new_x -= 0.1 * sin(game->player.dir);
		*new_y += 0.1 * cos(game->player.dir);
	}
	else if (game->player.side == 1)
	{
		*new_x -= 0.1 * sin(game->player.dir);
		*new_y -= 0.1 * cos(game->player.dir);
	}
	else if (game->player.side == 2)
	{
		*new_x += 0.1 * sin(game->player.dir);
		*new_y -= 0.1 * cos(game->player.dir);
	}
	else if (game->player.side == 3)
	{
		*new_x += 0.1 * sin(game->player.dir);
		*new_y += 0.1 * cos(game->player.dir);
	}
}

static void	keycode_d(t_gs *game, double *new_x, double *new_y)
{
	if (game->player.side == 0)
	{
		*new_x += 0.1 * sin(game->player.dir);
		*new_y -= 0.1 * cos(game->player.dir);
	}
	else if (game->player.side == 1)
	{
		*new_x += 0.1 * sin(game->player.dir);
		*new_y += 0.1 * cos(game->player.dir);
	}
	else if (game->player.side == 2)
	{
		*new_x -= 0.1 * sin(game->player.dir);
		*new_y += 0.1 * cos(game->player.dir);
	}
	else if (game->player.side == 3)
	{
		*new_x -= 0.1 * sin(game->player.dir);
		*new_y -= 0.1 * cos(game->player.dir);
	}
}

int	move(int keycode, t_gs *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (keycode == S)
		keycode_s(game, &new_x, &new_y);
	else if (keycode == W)
		keycode_w(game, &new_x, &new_y);
	else if (keycode == A)
		keycode_a(game, &new_x, &new_y);
	else if (keycode == D)
		keycode_d(game, &new_x, &new_y);
	if (game->map[(int)new_x][(int)new_y] == '0' && \
		game->map[(int)(new_x + 0.01)][(int)new_y] == '0' && \
		game->map[(int)new_x][(int)(new_y + 0.01)] == '0' && \
		game->map[(int)(new_x - 0.01)][(int)(new_y)] == '0' && \
		game->map[(int)(new_x)][(int)(new_y - 0.01)] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	return (1);
}
