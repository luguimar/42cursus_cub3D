/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:59:50 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/20 22:19:36 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	keycode_right_extra(t_gs *game)
{
	if (game->player.side == 2)
	{
		game->player.dir -= M_PI_2 / 12;
		if (game->player.dir < 0)
		{
			game->player.dir = -game->player.dir;
			game->player.side = 1;
		}
	}
	else if (game->player.side == 3)
	{
		game->player.dir += M_PI_2 / 12;
		if (game->player.dir > M_PI_2)
		{
			game->player.dir = M_PI_2 - game->player.dir + M_PI_2;
			game->player.side = 2;
		}
	}
}

void	keycode_right(t_gs *game)
{
	if (game->player.side == 0)
	{
		game->player.dir -= M_PI_2 / 12;
		if (game->player.dir < 0)
		{
			game->player.dir = -game->player.dir;
			game->player.side = 3;
		}
	}
	else if (game->player.side == 1)
	{
		game->player.dir += M_PI_2 / 12;
		if (game->player.dir > M_PI_2)
		{
			game->player.dir = M_PI_2 - game->player.dir + M_PI_2;
			game->player.side = 0;
		}
	}
	else
		keycode_right_extra(game);
}

void	keycode_left_extra(t_gs *game)
{
	if (game->player.side == 2)
	{
		game->player.dir += M_PI_2 / 12;
		if (game->player.dir > M_PI_2)
		{
			game->player.dir = M_PI_2 - game->player.dir + M_PI_2;
			game->player.side = 3;
		}
	}
	else if (game->player.side == 3)
	{
		game->player.dir -= M_PI_2 / 12;
		if (game->player.dir < 0)
		{
			game->player.dir = -game->player.dir;
			game->player.side = 0;
		}
	}
}

void	keycode_left(t_gs *game)
{
	if (game->player.side == 0)
	{
		game->player.dir += M_PI_2 / 12;
		if (game->player.dir < M_PI_2)
		{
			game->player.dir = M_PI_2 - game->player.dir + M_PI_2;
			game->player.side = 1;
		}
	}
	else if (game->player.side == 1)
	{
		game->player.dir -= M_PI_2 / 12;
		if (game->player.dir < 0)
		{
			game->player.dir = -game->player.dir;
			game->player.side = 2;
		}
	}
	else
		keycode_left_extra(game);
}

int	key_hook(int keycode, t_gs *game)
{
	if (keycode == ESC)
		mlx_close(game);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		move(keycode, game);
	else if (keycode == RIGHT)
		keycode_right(game);
	else if (keycode == LEFT)
		keycode_left(game);
	map_render(game);
	cube_render(game);
	minimaprender(game);
	mlx_clear_window(game->graphics.mlx, game->graphics.win);
	mlx_put_image_to_window(game->graphics.mlx, game->graphics.win, \
		game->graphics.img.img, 0, 0);
	return (0);
}
