/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 19:24:58 by jduraes-          #+#    #+#             */
/*   Updated: 2024/07/25 00:42:02 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_perror(char *str, int fd)
{
	ft_putstr_fd("Error: ", fd);
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
	gs->player = calloc(1, sizeof(t_position));
	return (gs);
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
	if (ft_strncmp(f + i, ".cub", 4))
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
	parser(argv[1], gs);
	if (!checker(gs))
		ft_perror("Invalid map format", 1);
	return (0);
}
