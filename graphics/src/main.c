/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:45:06 by luguimar          #+#    #+#             */
/*   Updated: 2024/07/25 08:33:38 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	mlx_pixel_put(game->graphics.mlx, game->graphics.win, y * 10 + j, x * 10 + i, 0xFFFFFF);
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
						mlx_pixel_put(game->graphics.mlx, game->graphics.win, j * 10 + k, i * 10 + l, 0x00FFFFFF);
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
						mlx_pixel_put(game->graphics.mlx, game->graphics.win, j * 10 + k, i * 10 + l, 0x00000000);
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
						mlx_pixel_put(game->graphics.mlx, game->graphics.win, j * 10 + k, i * 10 + l, 0x00FF0000);
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
				mlx_pixel_put(game->graphics.mlx, game->graphics.win, i, j, 0x00FF0000);
			else
				mlx_pixel_put(game->graphics.mlx, game->graphics.win, i, j, 0x0000FF00);
		}
	}
	return (1);
}

double	get_player_dir(char c)
{
	if (c == 'N')
		return (0);
	else if (c == 'E')
		return (M_PI_2);
	else if (c == 'S')
		return (M_PI);
	else if (c == 'W')
		return (3 * M_PI_2);
	return (0);
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
				game->player.dir = get_player_dir(game->map.map[i][j]);
				game->map.map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	put_line(t_game *game, double x, double y, double dir, int i)
{
	double	dist2wall;
	double	line_size;
	int		j;

	dist2wall = 0;
	while (game->map.map[(int)x][(int)y] == '0')
	{
		x += cos(dir);
		y += sin(dir);
		dist2wall += sqrt(pow(cos(dir), 2) + pow(sin(dir), 2));
	}
	line_size = 600 / dist2wall;
	j = 300 - line_size / 2;
	while (j < (300 + line_size))
	{
		mlx_pixel_put(game->graphics.mlx, game->graphics.win, i, j, 0x00FFFFFF);
		j++;
	}
}

void	cube_render(t_game *game)
{
	double	init_dir;
	double	end_dir;
	double	frac;
	int		i;

	init_dir = game->player.dir - M_PI_4 / 2;
	if (init_dir < 0)
		init_dir += 2 * M_PI;
	end_dir = game->player.dir + M_PI_4 / 2;
	if (end_dir >= 2 * M_PI)
		end_dir -= 2 * M_PI;
	frac = M_PI_4 / 2 / 800;
	i = 0;
	while (init_dir < end_dir && i < 800)
	{
		put_line(game, game->player.x, game->player.y, init_dir, i);
		init_dir += frac;
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
		new_x += 0.1 * cos(game->player.dir);
		new_y += 0.1 * sin(game->player.dir);
	}
	else if (keycode == W)
	{
		new_x -= 0.1 * cos(game->player.dir);
		new_y -= 0.1 * sin(game->player.dir);
	}
	else if (keycode == A)
	{
		new_x -= 0.1 * cos(game->player.dir + M_PI_2);
		new_y -= 0.1 * sin(game->player.dir + M_PI_2);
	}
	else if (keycode == D)
	{
		new_x += 0.1 * cos(game->player.dir + M_PI_2);
		new_y += 0.1 * sin(game->player.dir + M_PI_2);
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
		game->player.dir -= M_PI_2 / 12;
		if (game->player.dir < 0)
			game->player.dir += 2 * M_PI;
	}
	else if (keycode == LEFT)
	{
		game->player.dir += M_PI_2 / 12;
		if (game->player.dir >= 2 * M_PI)
			game->player.dir -= 2 * M_PI;
	}
	map_render(game);
	minimaprender(game);
	cube_render(game);
	return (0);
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
	map_render(game);
	minimaprender(game);
	cube_render(game);
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
