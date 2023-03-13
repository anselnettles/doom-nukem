/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:05:39 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 12:27:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	draw_skybox_collumn(t_drown *data, int x, int tx)
{
	int		y;
	int		ty;
	int		i;
	int		stretch;

	y = 0;
	ty = 0;
	stretch = (data->gfx.height) / 240;
	while (y < data->gfx.height)
	{
		i = 0;
		while (i < stretch && tx < 720)
		{
			pixel_put(&data->gfx, x, y + i,
				data->gfx.texture[SKYBOX].frame[0].pixels[tx + ty * 720]);
			i ++;
		}
		y += i;
		ty++;
	}
}

void	draw_skybox(t_drown *data)
{
	int		x;
	int		tx;
	int		stretch;
	int		i;

	x = 0;
	tx = (int)roundf((720.f / (360.f * (float)DEGREES)) * data->player.dir);
	stretch = (data->gfx.width * data->gfx.scale) / 320;
	if (tx < 0)
		tx *= -1;
	while (x < data->gfx.width)
	{
		if (tx >= 720)
		tx -= 720;
		i = 0;
		while (i < stretch)
		{
			draw_skybox_collumn(data, x + i, tx);
			i++;
		}
		x += i;
		tx++;
	}
}

int	render(t_drown *data)
{
	render_thread(data);
	if (data->system.overlay_toggle == TRUE)
		if (render_overlay(data) == ERROR)
			return (error(OVERLAY_ERROR));
	if (SDL_UpdateWindowSurface(data->gfx.window) == ERROR)
		return (ERROR);
	return (0);
}
