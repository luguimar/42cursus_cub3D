/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jduraes- <jduraes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 21:58:45 by jduraes-          #+#    #+#             */
/*   Updated: 2024/08/20 21:01:12 by jduraes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	flood_fill(t_gs *gs, int x, int y, char **map)
{
	static int	c;

	if (x < 0 || y < 0 || x >= gs->ylen || y >= gs->xlen)
	{
		c++;
		return (0);
	}
	if (map[x][y] == '1')
		return (1);
	else if (map[x][y] == ' ')
	{
		c++;
		return (0);
	}
	map[x][y] = '1';
	flood_fill(gs, x + 1, y, map);
	flood_fill(gs, x - 1, y, map);
	flood_fill(gs, x, y + 1, map);
	flood_fill(gs, x, y - 1, map);
	if (c > 0)
		return (0);
	return (1);
}

static int	wall_check(t_gs *gs)
{
	char	**tmap;
	int		i;

	i = -1;
	tmap = calloc(gs->ylen + 1, sizeof(char **));
	tmap[gs->ylen] = NULL;
	while (++i < gs->ylen)
		tmap[i] = ft_strdup(gs->map[i]);
	if (!flood_fill(gs, gs->playerp->y, gs->playerp->x, tmap))
	{
		doublefree(tmap);
		return (0);
	}
	else
		doublefree(tmap);
	return (1);
}

static int	player_check(t_gs *gs, int i, int j)
{
	int	c;

	c = 0;
	while (gs->map[++i] != NULL)
	{
		j = -1;
		while (gs->map[i][++j] != '\0')
		{
			if (gs->map[i][j] == 'N' || gs->map[i][j] == 'S'
				|| gs->map[i][j] == 'E' || gs->map[i][j] == 'W')
			{
				c++;
				gs->playerp->x = j;
				gs->playerp->y = i;
			}
		}
	}
	if (c != 1)
		return (0);
	return (1);
}

int	checker(t_gs *gs)
{
	if (!player_check(gs, -1, -1))
		return (0);
	if (!wall_check(gs))
		return (0);
	return (1);
}
