/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:13:57 by jduraes-          #+#    #+#             */
/*   Updated: 2024/08/02 17:55:54 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	rgbtohex(int *rgb)
{
	return ((rgb[0] << 16) + (rgb[1] << 8) + rgb[2]);
}

void	runitdown(int fd, char *line)
{
	free(line);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

int	check_info(t_gs *gs)
{
	if (gs->no_t == NULL || gs->so_t == NULL || gs->we_t == NULL
		|| gs->ea_t == NULL || gs->floor[0] == -1 || gs->ceiling[0] == -1)
		return (0);
	return (1);
}

int	copyconvert(char **s, int *a)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		a[i] = ft_atoi(s[i]);
	return (1);
}

int	t_access(char *s, char **d)
{
	char	*t;
	int		fd;

	t = ft_substr(s, 3, ft_strlen(s) - 3);
	*d = ft_strtrimfree(t, " \n");
	free(s);
	if (ft_strncmp(*d + ft_strlen(*d) - 4, ".xpm", 4))
	{
		printf("texture should be .xpm\n");
		return (0);
	}
	fd = open(*d, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("texture file not found\n", 1);
		return (0);
	}
	if (!(*d))
		return (0);
	return (1);
}
