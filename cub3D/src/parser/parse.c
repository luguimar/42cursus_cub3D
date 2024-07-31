/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 22:41:14 by jduraes-          #+#    #+#             */
/*   Updated: 2024/07/31 20:32:14 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	t_format(char *s, t_gs *gs)
{
	if (!ft_strncmp(s, "NO ", 3) && gs->no_t == NULL)
		return (t_access(s, &gs->no_t));
	else if (!ft_strncmp(s, "SO ", 3) && gs->so_t == NULL)
		return (t_access(s, &gs->so_t));
	else if (!ft_strncmp(s, "WE ", 3) && gs->we_t == NULL)
		return (t_access(s, &gs->we_t));
	else if (!ft_strncmp(s, "EA ", 3) && gs->ea_t == NULL)
		return (t_access(s, &gs->ea_t));
	free(s);
	return (0);
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
