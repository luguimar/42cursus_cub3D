/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:06:18 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/20 21:54:40 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + \
		x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	get_dir(char c)
{
	if (c == 'N')
		return (0);
	else if (c == 'E')
		return (M_PI_2);
	else if (c == 'S')
		return (0);
	else if (c == 'W')
		return (M_PI_2);
	return (0);
}

int	get_side(char c)
{
	if (c == 'N')
		return (2);
	else if (c == 'E')
		return (0);
	else if (c == 'S')
		return (0);
	else if (c == 'W')
		return (2);
	return (0);
}

void	get_player_dir(t_gs *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' \
			|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.dir = get_dir(game->map[i][j]);
				game->player.side = get_side(game->map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	get_player_position(t_gs *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S' \
			|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
			{
				game->player.x = ((double)i) + 0.5;
				game->player.y = ((double)j) + 0.5;
				get_player_dir(game);
				game->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}
