/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:41:14 by jduraes-          #+#    #+#             */
/*   Updated: 2024/07/25 00:42:44 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	t_format(char *s, t_gs *gs)
{
	static int	i;

	i++;
	if (i == 1 && !ft_strncmp(s, "NO ./", 5))
		gs->no_t = ft_substr(s, 3, ft_strlen(s) - 3);
	else if (i == 2 && !ft_strncmp(s, "SO ./", 5))
		gs->so_t = ft_substr(s, 3, ft_strlen(s) - 3);
	else if (i == 3 && !ft_strncmp(s, "WE ./", 5))
		gs->we_t = ft_substr(s, 3, ft_strlen(s) - 3);
	else if (i == 4 && !ft_strncmp(s, "EA ./", 5))
		gs->ea_t = ft_substr(s, 3, ft_strlen(s) - 3);
	else
		ft_perror("Error\ntexture format error\nshould be: \"NO ./texture\"\n",
			1);
}

static void	get_textures(char *full, t_gs *gs)
{
	char	**textures;
	int		i;

	textures = ft_split(full, '\n');
	if (!textures[0] || !textures[1] || !textures[2] || !textures[3])
		ft_perror("Error\nmissing texture info", 1);
	i = -1;
	while (textures[++i] != NULL)
		t_format(textures[i], gs);
	doublefree(textures);
	free(full);
}

static void	copyconvert(char **s, int *a)
{
	int	i;

	i = -1;
	while (s[++i] != NULL)
		a[i] = ft_atoi(s[i]);
}

static void	rgb_format(char *s, t_gs *gs)
{
	char	**temp;
	int		i;

	if (s[0] != 'F' && s[0] != 'C' && s[1] == ' ')
		ft_perror("wrong color format\nshould be \"C/F RGB,RGB,RGB\"", 1);
	temp = ft_split(s + 2, ',');
	if (ft_matlen(temp) != 3)
		ft_perror("wrong color format\nshould be \"C/F RGB,RGB,RGB\"", 1);
	i = -1;
	while (temp[++i] != NULL)
	{
		if (ft_atoi(temp[i]) < 0 || ft_atoi(temp[i]) > 255)
			ft_perror("error rgb number", 1);
	}
	if (s[0] == 'F')
		copyconvert(temp, gs->floor);
	if (s[0] == 'C')
		copyconvert(temp, gs->ceiling);
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

static void	strfill(char c, char *tofill, int len)
{
	int	i;

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

static int	map_write(int fd, t_gs *gs)
{
	char	*temp;
	char	*line;
	int		i;

	map_init(gs);
	line = get_next_line(fd);
	temp = NULL;
	i = -1;
	while (line && ++i < gs->ylen)
	{
		gs->map[i] = ft_memcpy(gs->map[i], line, ft_strlen(line) - 1);
		free(line);
		line = get_next_line(fd);
	}
	free(temp);
	free(line);
	return (1);
}

static int	info_write(char *f, t_gs *gs)
{
	int		fd;
	int		i;
	char	*line;
	char	*temp;

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
}

static int	length_aux(char *s, t_gs *gs)
{
	int			i;
	static int	pre;

	i = -1;
	if (pre++ < 8)
		return (1);
	else
	{
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
}

int	parser(char *f, t_gs *gs)
{
	int		fd;
	int		ic;
	char	*line;

	ic = 1;
	fd = open(f, O_RDONLY);
	line = get_next_line(fd);
	gs->xlen = 0;
	while (line && ic != 0)
	{
		ic = length_aux(line, gs);
		free(line);
		line = get_next_line(fd);
	}
	if (gs->ylen < 3 || gs->xlen < 3 || ic == 0)
		ft_perror("Invalid map", 1);
	free(line);
	return (info_write(f, gs));
}
