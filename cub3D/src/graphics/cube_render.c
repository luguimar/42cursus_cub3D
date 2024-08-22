/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 02:38:37 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/22 02:39:19 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	cube_render_aux_extra(int *side, double *dir)
{
	if (*side == 2)
	{
		*dir += M_PI_2 / 90 * 70 / 800;
		if (*dir > M_PI_2)
		{
			*dir = M_PI_2 - *dir + M_PI_2;
			*side = 3;
		}
	}
	else if (*side == 3)
	{
		*dir -= M_PI_2 / 90 * 70 / 800;
		if (*dir < 0)
		{
			*dir = -(*dir);
			*side = 0;
		}
	}
}

static void	cube_render_aux(int *side, double *dir)
{
	if (*side == 0)
	{
		*dir += M_PI_2 / 90 * 70 / 800;
		if (*dir > M_PI_2)
		{
			*dir = M_PI_2 - *dir + M_PI_2;
			*side = 1;
		}
	}
	else if (*side == 1)
	{
		*dir -= M_PI_2 / 90 * 70 / 800;
		if (*dir < 0)
		{
			*dir = -(*dir);
			*side = 2;
		}
	}
	else
		cube_render_aux_extra(side, dir);
}

static void	cube_render_aux2_extra(int *side, double *dir)
{
	if (*side == 2)
	{
		*dir -= M_PI_2 / 90 * 70 / 800;
		if (*dir < 0)
		{
			*dir = -(*dir);
			*side = 1;
		}
	}
	else if (*side == 3)
	{
		*dir += M_PI_2 / 90 * 70 / 800;
		if (*dir > M_PI_2)
		{
			*dir = M_PI_2 - *dir + M_PI_2;
			*side = 2;
		}
	}
}

static void	cube_render_aux2(int *side, double *dir)
{
	if (*side == 0)
	{
		*dir -= M_PI_2 / 90 * 70 / 800;
		if (*dir < 0)
		{
			*dir = -(*dir);
			*side = 3;
		}
	}
	else if (*side == 1)
	{
		*dir += M_PI_2 / 90 * 70 / 800;
		if (*dir > M_PI_2)
		{
			*dir = M_PI_2 - *dir + M_PI_2;
			*side = 0;
		}
	}
	else
		cube_render_aux2_extra(side, dir);
}

void	cube_render(t_gs *game)
{
	int		i;
	double	dir;
	int		side;

	i = -1;
	dir = game->player.dir;
	side = game->player.side;
	while (++i < 400)
		cube_render_aux(&side, &dir);
	i = -1;
	while (++i < 800)
	{
		cube_render_aux2(&side, &dir);
		put_line(game, dir, side, i);
	}
}
