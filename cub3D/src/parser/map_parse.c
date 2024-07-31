/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:12:35 by jduraes-          #+#    #+#             */
/*   Updated: 2024/07/31 21:29:22 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	strfill(char c, char *tofill, int len)
{
	int i;

	i = -1;
	while (++i < len)
		tofill[i] = c;
}

static void	map_init(t_gs *gs)
{
	int	i;

	i = -1;
	gs->map = malloc(sizeof(char *) * (gs->ylen + 1));
	if (!gs->map)
		return ;
	gs->map[gs->ylen] = NULL;
	while (++i < gs->ylen)
	{
		gs->map[i] = malloc(sizeof(char) * (gs->xlen + 1));
		if (!gs->map[i])
			return ;
		gs->map[i][gs->xlen] = '\0';
		strfill(' ', gs->map[i], gs->xlen);
	}
}

static int	map_write(t_gs *gs, char *f)
{
	char	*line;
	int		i;
	int		fd;

	map_init(gs);
	fd = open(f, O_RDONLY);
	line = get_next_line(fd);
	i = 0;
	while (i < 6 || !ft_strncmp(line, "\n", ft_strlen(line)))
	{
		if (ft_strncmp(line, "\n", ft_strlen(line)))
			i++;
		free(line);
		line = get_next_line(fd);
	}
	i = -1;
	while (line && ++i < gs->ylen)
	{
		gs->map[i] = ft_memcpy(gs->map[i], line, ft_strlen(line) - 1);
		free(line);
		line = get_next_line(fd);
	}
	runitdown(fd, line);
	return (1);
}

static int	length_aux(char *s, t_gs *gs)
{
	int	i;

	i = -1;
	while (s[++i] != '\0' && s[i] != '\n')
	{
		if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'E' && s[i] != 'W' && s[i] != ' ')
			return (0);
	}
	gs->ylen++;
	if (gs->xlen < (int)ft_strlen(s) - 1)
		gs->xlen = ft_strlen(s) - 1;
	return (1);
}

int	map_start(int fd, t_gs *gs, char *f)
{
	char	*l;

	l = get_next_line(fd);
	while (l && !ft_strncmp(l, "\n", ft_strlen(l)))
	{
		free(l);
		l = get_next_line(fd);
	}
	while (l)
	{
		if (!length_aux(l, gs))
		{
			free(l);
			return (0);
		}
		free(l);
		l = get_next_line(fd);
	}
	if (l)
		free(l);
	if (gs->xlen < 3 || gs->ylen < 3)
		return (0);
	return (map_write(gs, f));
}

