/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 00:59:50 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/16 02:11:21 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	move(int keycode, t_gs *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x;
	new_y = game->player.y;
	if (keycode == S)
	{
		if (game->player.side == 0)
		{
			new_x -= 0.1 * cos(game->player.dir);
			new_y -= 0.1 * sin(game->player.dir);
		}
		else if (game->player.side == 1)
		{
			new_x += 0.1 * cos(game->player.dir);
			new_y -= 0.1 * sin(game->player.dir);
		}
		else if (game->player.side == 2)
		{
			new_x += 0.1 * cos(game->player.dir);
			new_y += 0.1 * sin(game->player.dir);
		}
		else if (game->player.side == 3)
		{
			new_x -= 0.1 * cos(game->player.dir);
			new_y += 0.1 * sin(game->player.dir);
		}
	}
	else if (keycode == W)
	{
		if (game->player.side == 0)
		{
			new_x += 0.1 * cos(game->player.dir);
			new_y += 0.1 * sin(game->player.dir);
		}
		else if (game->player.side == 1)
		{
			new_x -= 0.1 * cos(game->player.dir);
			new_y += 0.1 * sin(game->player.dir);
		}
		else if (game->player.side == 2)
		{
			new_x -= 0.1 * cos(game->player.dir);
			new_y -= 0.1 * sin(game->player.dir);
		}
		else if (game->player.side == 3)
		{
			new_x += 0.1 * cos(game->player.dir);
			new_y -= 0.1 * sin(game->player.dir);
		}
	}
	else if (keycode == A)
	{
		if (game->player.side == 0)
		{
			new_x -= 0.1 * sin(game->player.dir);
			new_y += 0.1 * cos(game->player.dir);
		}
		else if (game->player.side == 1)
		{
			new_x -= 0.1 * sin(game->player.dir);
			new_y -= 0.1 * cos(game->player.dir);
		}
		else if (game->player.side == 2)
		{
			new_x += 0.1 * sin(game->player.dir);
			new_y -= 0.1 * cos(game->player.dir);
		}
		else if (game->player.side == 3)
		{
			new_x += 0.1 * sin(game->player.dir);
			new_y += 0.1 * cos(game->player.dir);
		}
	}
	else if (keycode == D)
	{
		if (game->player.side == 0)
		{
			new_x += 0.1 * sin(game->player.dir);
			new_y -= 0.1 * cos(game->player.dir);
		}
		else if (game->player.side == 1)
		{
			new_x += 0.1 * sin(game->player.dir);
			new_y += 0.1 * cos(game->player.dir);
		}
		else if (game->player.side == 2)
		{
			new_x -= 0.1 * sin(game->player.dir);
			new_y += 0.1 * cos(game->player.dir);
		}
		else if (game->player.side == 3)
		{
			new_x -= 0.1 * sin(game->player.dir);
			new_y -= 0.1 * cos(game->player.dir);
		}
	}
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

int	key_hook(int keycode, t_gs *game)
{
	if (keycode == ESC)
		mlx_close(game);
	else if (keycode == W || keycode == A || keycode == S || keycode == D)
		move(keycode, game);
	else if (keycode == RIGHT)
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
		else if (game->player.side == 2)
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
	else if (keycode == LEFT)
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
		else if (game->player.side == 2)
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
	map_render(game);
	cube_render(game);
	minimaprender(game);
	mlx_clear_window(game->graphics.mlx, game->graphics.win);
	mlx_put_image_to_window(game->graphics.mlx, game->graphics.win, \
		game->graphics.img.img, 0, 0);
	return (0);
}
