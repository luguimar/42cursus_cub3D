/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:45:06 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/07 05:49:23 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + \
		x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	playerrender(t_game *game)
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

int	minimaprender(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == '1')
			{
				k = 0;
				while (k < 10)
				{
					l = 0;
					while (l < 10)
					{
						my_pixel_put(&game->graphics.img, j * 10 + k, i * 10 + l, 0x00FFFFFF);
						l++;
					}
					k++;
				}
			}
			else if (game->map.map[i][j] == '0' || game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' || game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				k = 0;
				while (k < 10)
				{
					l = 0;
					while (l < 10)
					{
						my_pixel_put(&game->graphics.img, j * 10 + k, i * 10 + l, 0x00000000);
						l++;
					}
					k++;
				}
			}
			else if (game->map.map[i][j] == ' ')
			{
				k = 0;
				while (k < 10)
				{
					l = 0;
					while (l < 10)
					{
						my_pixel_put(&game->graphics.img, j * 10 + k, i * 10 + l, 0x00FF0000);
						l++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
	playerrender(game);
	return (1);
}

int	error_msg(char *msg, int ret)
{
	ft_putstr_fd(msg, 2);
	return (ret);
}

int	mlx_close(t_game *game)
{
	mlx_destroy_window(game->graphics.mlx, game->graphics.win);
	mlx_destroy_display(game->graphics.mlx);
	free(game->graphics.mlx);
	free_array_of_strings(game->map.map);
	exit(0);
}

static int	check_extension(char *str, char *ext)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (ext[j])
		j++;
	if (i < j)
		return (0);
	while (j >= 0)
	{
		if (str[i] != ext[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

int	map_render(t_game *game)
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
				my_pixel_put(&game->graphics.img, i, j, 0x00FF0000);
			else
				my_pixel_put(&game->graphics.img, i, j, 0x0000FF00);
		}
	}
	return (1);
}

double	get_dir(char c)
{
	if (c == 'N')
		return (0);
	else if (c == 'E')
		return (M_PI_2);
	else if (c == 'S')
		return (0);
	else if (c == 'W')
		return (M_PI_2);
	return (0);
}

int	get_side(char c)
{
	if (c == 'N')
		return (2);
	else if (c == 'E')
		return (0);
	else if (c == 'S')
		return (0);
	else if (c == 'W')
		return (2);
	return (0);
}

void	get_player_dir(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' || game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				game->player.dir = get_dir(game->map.map[i][j]);
				game->player.side = get_side(game->map.map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	get_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' || game->map.map[i][j] == 'E' || game->map.map[i][j] == 'W')
			{
				game->player.x = ((double)i) + 0.5;
				game->player.y = ((double)j) + 0.5;
				get_player_dir(game);
				game->map.map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	put_line(t_game *game, double x, double y, double dir, int side, int i)
{
	double	dist2wall;
	double	line_size;
	int		j;

	dist2wall = 0;
	if (side == 0)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x += 0.1 * cos(dir);
			y += 0.1 * sin(dir);
			dist2wall += 0.1;
		}
		while (game->map.map[(int)x][(int)y] == '1')
		{
			x -= 0.01 * cos(dir);
			y -= 0.01 * sin(dir);
			dist2wall -= 0.01;
		}
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x += 0.001 * cos(dir);
			y += 0.001 * sin(dir);
			dist2wall += 0.001;
		}
	}
	else if (side == 1)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x -= 0.1 * cos(dir);
			y += 0.1 * sin(dir);
			dist2wall += 0.1;
		}
		while (game->map.map[(int)x][(int)y] == '1')
		{
			x += 0.01 * cos(dir);
			y -= 0.01 * sin(dir);
			dist2wall -= 0.01;
		}
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x -= 0.001 * cos(dir);
			y += 0.001 * sin(dir);
			dist2wall += 0.001;
		}
	}
	else if (side == 2)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x -= 0.1 * cos(dir);
			y -= 0.1 * sin(dir);
			dist2wall += 0.1;
		}
		while (game->map.map[(int)x][(int)y] == '1')
		{
			x += 0.01 * cos(dir);
			y += 0.01 * sin(dir);
			dist2wall -= 0.01;
		}
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x -= 0.001 * cos(dir);
			y -= 0.001 * sin(dir);
			dist2wall += 0.001;
		}
	}
	else if (side == 3)
	{
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x += 0.1 * cos(dir);
			y -= 0.1 * sin(dir);
			dist2wall += 0.1;
		}
		while (game->map.map[(int)x][(int)y] == '1')
		{
			x -= 0.01 * cos(dir);
			y += 0.01 * sin(dir);
			dist2wall -= 0.01;
		}
		while (game->map.map[(int)x][(int)y] != '1')
		{
			x += 0.001 * cos(dir);
			y -= 0.001 * sin(dir);
			dist2wall += 0.001;
		}
	}
	line_size = 1 / dist2wall * 600 * (45.0 / 70.0);
	if (line_size > 600)
		line_size = 600;
	j = 0;
	while (j < line_size)
	{
		my_pixel_put(&game->graphics.img, i, j + 300 - line_size / 2, 0x00FFFFFF);
		j++;
	}
}

void	cube_render(t_game *game)
{
	int		i;
	double	dir;
	int		side;

	i = 0;
	dir = game->player.dir;
	side = game->player.side;
	while (i < 400)
	{
		if (side == 0)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 1;
			}
		}
		else if (side == 1)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 2;
			}
		}
		else if (side == 2)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 3;
			}
		}
		else if (side == 3)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 0;
			}
		}
		i++;
	}
	i = 0;
	while (i < 800)
	{
		if (side == 0)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 3;
			}
		}
		else if (side == 1)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 0;
			}
		}
		else if (side == 2)
		{
			dir -= M_PI_2 / 90 * 70 / 800;
			if (dir < 0)
			{
				dir = -dir;
				side = 1;
			}
		}
		else if (side == 3)
		{
			dir += M_PI_2 / 90 * 70 / 800;
			if (dir > M_PI_2)
			{
				dir = M_PI_2 - dir + M_PI_2;
				side = 2;
			}
		}
		put_line(game, game->player.x, game->player.y, dir, side, i);
		i++;
	}
}

int	move(int keycode, t_game *game)
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
			new_x -= 0.1 * cos(game->player.dir);
			new_y -= 0.1 * sin(game->player.dir);
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
			new_x += 0.1 * cos(game->player.dir);
			new_y += 0.1 * sin(game->player.dir);
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
	if (game->map.map[(int)new_x][(int)new_y] == '0')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	return (1);
}

int	key_hook(int keycode, t_game *game)
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

void	init_img(t_img *img, void *mlx, int width, int height)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
		&img->line_length, &img->endian);
}

void	mlx_start(t_game *game)
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
	//set_mlx_images(game);
	get_player_position(game);
	init_img(&game->graphics.img, game->graphics.mlx, 800, 600);
	my_pixel_put(&game->graphics.img, 400, 300, 0x00FFFFFF);
	map_render(game);
	cube_render(game);
	minimaprender(game);
	mlx_clear_window(game->graphics.mlx, game->graphics.win);
	mlx_put_image_to_window(game->graphics.mlx, game->graphics.win, \
		game->graphics.img.img, 0, 0);
	mlx_hook(game->graphics.win, 2, 1L << 0, key_hook, game);
	mlx_hook(game->graphics.win, 17, 0, mlx_close, game);
	//mlx_loop_hook(game->graphics.mlx, map_render, game);
	mlx_loop(game->graphics.mlx);
}

int	check_map(char *file, t_game *game)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		i++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	game->map.map = malloc(sizeof(char *) * (i + 1));
	if (!game->map.map)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		game->map.map[i] = ft_strdup(line);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	game->map.map[i] = NULL;
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (error_msg("Error\n Invalid number of arguments", 0));
	if (!check_extension(argv[1], ".cub"))
		return (error_msg("Error\n Invalid file extension\n", 0));
	if (!check_map(argv[1], &game))
		return (error_msg("Error\n Invalid map\n", 0));
	mlx_start(&game);
	return (0);
}
