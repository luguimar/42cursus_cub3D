/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:44:49 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/22 01:46:08 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	minimap_render_aux_aux_aux(t_gs *game, int i, int j, int color)
{
	int	k;
	int	l;

	k = 0;
	while (k < 10)
	{
		l = 0;
		while (l < 10)
		{
			my_pixel_put(&game->graphics.img, j * 10 + k, i * 10 + l, color);
			l++;
		}
		k++;
	}
}

static void	minimap_render_aux_aux(t_gs *game, int i, int j)
{
	if (game->map[i][j] == '1')
		minimap_render_aux_aux_aux(game, i, j, 0x00FFFFFF);
	else if (game->map[i][j] == '0' || game->map[i][j] == 'N' || \
	game->map[i][j] == 'S' || game->map[i][j] == 'E' || game->map[i][j] == 'W')
		minimap_render_aux_aux_aux(game, i, j, 0x00000000);
	else if (game->map[i][j] == ' ')
		minimap_render_aux_aux_aux(game, i, j, 0x00FF0000);
}

static void	minimap_render_aux(t_gs *game, int i)
{
	int	j;

	j = 0;
	while (game->map[i][j])
	{
		minimap_render_aux_aux(game, i, j);
		j++;
	}
}

int	minimaprender(t_gs *game)
{
	int	i;

	i = 0;
	while (game->map[i])
	{
		minimap_render_aux(game, i);
		i++;
	}
	playerrender(game);
	return (1);
}
