/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:41:14 by jduraes-          #+#    #+#             */
/*   Updated: 2024/07/29 21:47:42 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
static void	get_textures(char *full, t_gs *gs)
{
	char	**textures;
	int		i;

	textures = ft_split(full, '\n');
	if (!textures[0] ||!textures[1] ||!textures[2] ||!textures[3])
		ft_perror("Error\nmissing texture info", 1);
	i = -1;
	while (textures[++i] != NULL)
		t_format(textures[i], gs);
	doublefree(textures);
	free(full);
}

static void	get_rgb(char *full, t_gs *gs)
{
	char	**rgb;

	rgb = ft_split(full, '\n');
	if (!rgb[0] || !rgb[1])
	{
		ft_perror("missing color info", 1);
	}
	rgb_format(rgb[0], gs);
	rgb_format(rgb[1], gs);
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

static int	info_write(char *f, t_gs *gs)
{
	int		fd;
	int		i;
	char	*line;
	char	*temp;
	int		i;

	i = -1;
	fd = open(f, O_RDONLY);
	temp = NULL;
	line = get_next_line(fd);
	while (line && ++i < 4)
	{
		temp = ft_strjoinfree(temp, line, 3);
		line = get_next_line(fd);
	}
	free(line);
	get_textures(temp, gs);
	temp = NULL;
	line = get_next_line(fd);
	while (line && ++i < 7)
	{
		temp = ft_strjoinfree(temp, line, 3);
		line = get_next_line(fd);
	}
	get_rgb(temp, gs);
	return (map_write(fd, gs));
}*/
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

static void	runitdown(int fd, char *line)
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

static int	map_write(t_gs *gs, char *f)
{
	char	*temp;
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
	temp = NULL;
	i = -1;
	while (line && ++i < gs->ylen)
	{
		gs->map[i] = ft_memcpy(gs->map[i], line, ft_strlen(line) - 1);
		free(line);
		line = get_next_line(fd);
	}
	free(temp);
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
	if (ft_strlen(s) < 3)
		return (0);
	return (1);
}

static int	map_start(int fd, t_gs *gs, char *f)
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
	return (map_write(gs, f));
}

static int	t_access(char *s, char **d)
{
	char	*t;

	t = ft_substr(s, 3, ft_strlen(s) - 3);
	*d = ft_strtrimfree(t, " ");
	free(s);
	if (!(*d))
		return (0);
	return (1);
}

static int	t_format(char *s, t_gs *gs)
{
	if (!ft_strncmp(s, "NO ", 3) && gs->no_t == NULL)
	{
		t_access(s, &gs->no_t);
		return (1);
	}
	else if (!ft_strncmp(s, "SO ", 3) && gs->so_t == NULL)
	{
		t_access(s, &gs->so_t);
		return (1);
	}
	else if (!ft_strncmp(s, "WE ", 3) && gs->we_t == NULL)
	{
		t_access(s, &gs->we_t);
		return (1);
	}
	else if (!ft_strncmp(s, "EA ", 3) && gs->ea_t == NULL)
	{
		t_access(s, &gs->ea_t);
		return (1);
	}
	free(s);
	return (0);
}

static int	copyconvert(char **s, int *a)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		a[i] = ft_atoi(s[i]);
	return (1);
}

static int	checkvalues(char **s, t_gs *gs, char c)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i] != NULL)
	{
		j = -1;
		s[i] = ft_strtrimfree(s[i], " \n");
		while (s[i][++j] != '\0')
		{
			if (!ft_isdigit(s[i][j]))
				return (0);
		}
		if (ft_atoi(s[i]) < 0 || ft_atoi(s[i]) > 255)
		{
			printf("invalid RGB number");
			return (0);
		}
	}
	if (c == 'F' && gs->floor[0] == -1)
		return (copyconvert(s, gs->floor));
	else if (c == 'C' && gs->ceiling[0] == -1)
		return (copyconvert(s, gs->ceiling));
	return (0);
}

static int	rgb_format(char *s, t_gs *gs)
{
	char	**temp;

	if (s[1] != ' ')
	{
		free(s);
		return (0);
	}
	temp = ft_split(s + 2, ',');
	if (ft_matlen(temp) != 3)
	{
		printf("wrong color format\nshould be \"C/F RGB,RGB,RGB\"");
		doublefree(temp);
		free(s);
		return (0);
	}
	if (!checkvalues(temp, gs, s[0]))
	{
		doublefree(temp);
		free(s);
		return (0);
	}
	doublefree(temp);
	free(s);
	return (1);
}

static int	check_format(char *line, t_gs *gs)
{
	char	*s;

	s = ft_strtrim(line, " ");
	if (!ft_strncmp(s, "\n", ft_strlen(line)))
	{
		free(s);
		return (1);
	}
	else if (s[0] == 'F' || s[0] == 'C')
		return (rgb_format(s, gs));
	else if (!ft_strncmp(s, "NO", 2) || !ft_strncmp(s, "SO", 2)
		|| !ft_strncmp(s, "EA", 2) || !ft_strncmp(s, "WE", 2))
		return (t_format(s, gs));
	free(s);
	return (0);
}

static int	check_info(t_gs *gs)
{
	if (gs->no_t == NULL || gs->so_t == NULL || gs->we_t == NULL
		|| gs->ea_t == NULL || gs->floor[0] == -1 || gs->ceiling[0] == -1)
		return (0);
	return (1);
}

int	parser(char *f, t_gs *gs)
{
	int		fd;
	char	*line;

	fd = open(f, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!check_format(line, gs) && ft_strncmp(line, "\n", ft_strlen(line)))
		{
			runitdown(fd, line);
			;
			return (0);
		}
		free(line);
		if (check_info(gs))
			break ;
		line = get_next_line(fd);
	}
	if (!check_info(gs))
	{
		free(line);
		return (0);
	}
	return (map_start(fd, gs, f));
}
