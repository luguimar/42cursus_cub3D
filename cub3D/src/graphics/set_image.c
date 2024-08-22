/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:47:42 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/20 21:53:33 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	set_image0(t_gs *game, char *path)
{
	game->graphics.no.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
		&game->graphics.no.width, &game->graphics.no.height);
	if (!game->graphics.no.img)
		return (1);
	game->graphics.no.addr = mlx_get_data_addr(game->graphics.no.img, \
		&game->graphics.no.bits_per_pixel, &game->graphics.no.line_length, \
		&game->graphics.no.endian);
	return (0);
}

int	set_image1(t_gs *game, char *path)
{
	game->graphics.so.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
		&game->graphics.so.width, &game->graphics.so.height);
	if (!game->graphics.so.img)
		return (1);
	game->graphics.so.addr = mlx_get_data_addr(game->graphics.so.img, \
		&game->graphics.so.bits_per_pixel, &game->graphics.so.line_length, \
		&game->graphics.so.endian);
	return (0);
}

int	set_image2(t_gs *game, char *path)
{
	game->graphics.ea.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
		&game->graphics.ea.width, &game->graphics.ea.height);
	if (!game->graphics.ea.img)
		return (1);
	game->graphics.ea.addr = mlx_get_data_addr(game->graphics.ea.img, \
		&game->graphics.ea.bits_per_pixel, &game->graphics.ea.line_length, \
		&game->graphics.ea.endian);
	return (0);
}

int	set_image3(t_gs *game, char *path)
{
	game->graphics.we.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
		&game->graphics.we.width, &game->graphics.we.height);
	if (!game->graphics.we.img)
		return (1);
	game->graphics.we.addr = mlx_get_data_addr(game->graphics.we.img, \
		&game->graphics.we.bits_per_pixel, &game->graphics.we.line_length, \
		&game->graphics.we.endian);
	return (0);
}

int	set_image(t_gs *game, char *path, int i)
{
	if (i == 0)
	{
		if (set_image0(game, path))
			return (1);
	}
	else if (i == 1)
	{
		if (set_image1(game, path))
			return (1);
	}
	else if (i == 2)
	{
		if (set_image2(game, path))
			return (1);
	}
	else if (i == 3)
	{
		if (set_image3(game, path))
			return (1);
	}
	return (0);
}
