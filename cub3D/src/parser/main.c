/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:24:58 by jduraes-          #+#    #+#             */
/*   Updated: 2024/08/16 05:32:43 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_perror(char *str, int fd)
{
	ft_putstr_fd("Error\n", fd);
	ft_putstr_fd(str, fd);
	ft_putstr_fd("\n", fd);
	exit(EXIT_FAILURE);
}

static t_gs	*gs_init(void)
{
	t_gs	*gs;

	gs = (t_gs *)ft_calloc(1, sizeof(t_gs));
	if (!gs)
		ft_perror("gamestate init error", 1);
	gs->playerp = ft_calloc(1, sizeof(t_position));
	gs->floor[0] = -1;
	gs->ceiling[0] = -1;
	return (gs);
}

void	deinitialize(t_gs *gs)
{
	if (gs)
	{
		if (gs->map)
			doublefree(gs->map);
		if (gs->playerp)
			free(gs->playerp);
		if (gs->no_t)
			free(gs->no_t);
		if (gs->so_t)
			free(gs->so_t);
		if (gs->we_t)
			free(gs->we_t);
		if (gs->ea_t)
			free(gs->ea_t);
		free(gs);
	}
}

static void	is_valid(char *f)
{
	int	fd;
	int	i;

	i = -1;
	while (f[++i] != '.' && f[i] != '\0')
	{
		if (f[i] == '\0')
			ft_perror("Invalid map format", 1);
	}
	if (ft_strncmp(f + i, ".cub\0", 5))
		ft_perror("Invalid map format", 1);
	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_perror("Map doesnt exist", 1);
}

int	main(int argc, char **argv)
{
	t_gs	*gs;

	if (argc != 2)
		ft_perror("wrong number of arguments", 1);
	is_valid(argv[1]);
	gs = gs_init();
	if (!parser(argv[1], gs))
	{
		deinitialize(gs);
		ft_perror("Invalid map", 1);
	}
	if (!checker(gs))
	{
		deinitialize(gs);
		ft_perror("Invalid map", 1);
	}
	mlx_start(gs);
	deinitialize(gs);
	return (0);
}
