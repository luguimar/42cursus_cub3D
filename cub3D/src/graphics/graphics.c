/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:45:06 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/15 02:04:42 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + \
		x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	error_msg(char *msg, int ret)
{
	ft_putstr_fd(msg, 2);
	return (ret);
}

int	set_image(t_gs *game, char *path, int i)
{
	if (i == 0)
	{
		game->graphics.no.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
			&game->graphics.no.width, &game->graphics.no.height);
		game->graphics.no.addr = mlx_get_data_addr(game->graphics.no.img, \
			&game->graphics.no.bits_per_pixel, &game->graphics.no.line_length, \
			&game->graphics.no.endian);
	}
	else if (i == 1)
	{
		game->graphics.so.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
			&game->graphics.so.width, &game->graphics.so.height);
		game->graphics.so.addr = mlx_get_data_addr(game->graphics.so.img, \
			&game->graphics.so.bits_per_pixel, &game->graphics.so.line_length, \
			&game->graphics.so.endian);
	}
	else if (i == 2)
	{
		game->graphics.ea.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
			&game->graphics.ea.width, &game->graphics.ea.height);
		game->graphics.ea.addr = mlx_get_data_addr(game->graphics.ea.img, \
			&game->graphics.ea.bits_per_pixel, &game->graphics.ea.line_length, \
			&game->graphics.ea.endian);
	}
	else if (i == 3)
	{
		game->graphics.we.img = mlx_xpm_file_to_image(game->graphics.mlx, path, \
			&game->graphics.we.width, &game->graphics.we.height);
		game->graphics.we.addr = mlx_get_data_addr(game->graphics.we.img, \
			&game->graphics.we.bits_per_pixel, &game->graphics.we.line_length, \
			&game->graphics.we.endian);
	}
	if (!game->graphics.no.img)
		return (error_msg("Error\nmlx_xpm_file_to_image failed\n", 1));
	return (0);
}

int	set_mlx_images(t_gs *game)
{
	if (set_image(game, game->no_t, 0))
		return (1);
	if (set_image(game, game->so_t, 1))
		return (1);
	if (set_image(game, game->ea_t, 2))
		return (1);
	if (set_image(game, game->we_t, 3))
		return (1);
	return (0);
}

int	mlx_close(t_gs *game)
{
	mlx_destroy_window(game->graphics.mlx, game->graphics.win);
	mlx_destroy_display(game->graphics.mlx);
	free(game->graphics.mlx);
	doublefree(game->map);
	exit(0);
}

void	init_img(t_img *img, void *mlx, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
}

void	mlx_start(t_gs *game)
{
	game->graphics.mlx = mlx_init();
	if (!game->graphics.mlx)
	{
		ft_putstr_fd("Error\nmlx_init failed\n", 2);
		exit(1);
	}
	game->graphics.win = mlx_new_window(game->graphics.mlx, 800, 600, "cub3D");
	if (!game->graphics.win)
	{
		mlx_destroy_display(game->graphics.mlx);
		ft_putstr_fd("Error\nmlx_new_window failed\n", 2);
		exit(1);
	}
	if (set_mlx_images(game))
	{
		mlx_destroy_display(game->graphics.mlx);
		ft_putstr_fd("Error\nmlx_xpm_file_to_image failed fuck it\n", 2);
		exit(1);
	}
	get_player_position(game);
	init_img(&game->graphics.img, game->graphics.mlx, 800, 600);
	map_render(game);
	cube_render(game);
	minimaprender(game);
	mlx_clear_window(game->graphics.mlx, game->graphics.win);
	mlx_put_image_to_window(game->graphics.mlx, game->graphics.win, \
		game->graphics.img.img, 0, 0);
	mlx_hook(game->graphics.win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->graphics.win, 17, 0, mlx_close, game);
	mlx_loop(game->graphics.mlx);
}
