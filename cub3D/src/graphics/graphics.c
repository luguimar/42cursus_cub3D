/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:45:06 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/20 21:54:49 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	error_msg(char *msg, int ret)
{
	ft_putstr_fd(msg, 2);
	return (ret);
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
	deinitialize(game);
	exit(0);
}

int	init_img(t_img *img, void *mlx, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	if (!img->img)
	{
		ft_putstr_fd("Error\nmlx_new_image failed\n", 2);
		return (1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
	return (0);
}

void	mlx_start(t_gs *game)
{
	game->graphics.mlx = mlx_init();
	if (!game->graphics.mlx)
		ft_perror("mlx_init failed", 2, game);
	game->graphics.win = mlx_new_window(game->graphics.mlx, 800, 600, "cub3D");
	if (!game->graphics.win)
		ft_perror("mlx_new_window failed", 2, game);
	if (set_mlx_images(game))
		ft_perror("mlx_xpm_file_to_image failed", 2, game);
	get_player_position(game);
	if (init_img(&game->graphics.img, game->graphics.mlx, 800, 600))
		deinitialize(game);
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
