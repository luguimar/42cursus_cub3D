/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinitialize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguimar <luguimar@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 02:56:33 by luguimar          #+#    #+#             */
/*   Updated: 2024/08/22 02:57:52 by luguimar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	deinitialize_aux(t_gs *gs)
{
	if (gs->graphics.no.img)
		mlx_destroy_image(gs->graphics.mlx, gs->graphics.no.img);
	if (gs->graphics.so.img)
		mlx_destroy_image(gs->graphics.mlx, gs->graphics.so.img);
	if (gs->graphics.ea.img)
		mlx_destroy_image(gs->graphics.mlx, gs->graphics.ea.img);
	if (gs->graphics.we.img)
		mlx_destroy_image(gs->graphics.mlx, gs->graphics.we.img);
	if (gs->graphics.img.img)
		mlx_destroy_image(gs->graphics.mlx, gs->graphics.img.img);
	if (gs->graphics.win)
		mlx_destroy_window(gs->graphics.mlx, gs->graphics.win);
	if (gs->graphics.mlx)
	{
		mlx_destroy_display(gs->graphics.mlx);
		free(gs->graphics.mlx);
	}
}

void	deinitialize(t_gs *gs)
{
	if (gs)
	{
		if (gs->map)
			doublefree(gs->map);
		if (gs->playerp)
			free(gs->playerp);
		if (gs->no_t)
			free(gs->no_t);
		if (gs->so_t)
			free(gs->so_t);
		if (gs->we_t)
			free(gs->we_t);
		if (gs->ea_t)
			free(gs->ea_t);
		deinitialize_aux(gs);
		free(gs);
	}
}
