/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:24:58 by jduraes-          #+#    #+#             */
/*   Updated: 2024/08/22 02:59:08 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_perror(char *str, int fd, t_gs *gs)
{
	deinitialize(gs);
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
		ft_perror("gamestate init error", 1, NULL);
	gs->playerp = ft_calloc(1, sizeof(t_position));
	gs->floor[0] = -1;
	gs->ceiling[0] = -1;
	return (gs);
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

static void	is_valid(char *f, t_gs *gs)
{
	int	fd;
	int	i;

	i = -1;
	if (!check_extension(f, ".cub"))
		ft_perror("Invalid file extension", 1, gs);
	fd = open(f, O_RDONLY);
	if (fd == -1)
		ft_perror("Map doesnt exist", 1, gs);
}

int	main(int argc, char **argv)
{
	t_gs	*gs;

	gs = gs_init();
	if (argc != 2)
		ft_perror("wrong number of arguments", 1, gs);
	is_valid(argv[1], gs);
	if (!parser(argv[1], gs))
		ft_perror("Invalid map", 1, gs);
	if (!checker(gs))
		ft_perror("Invalid map", 1, gs);
	mlx_start(gs);
	deinitialize(gs);
	return (0);
}
