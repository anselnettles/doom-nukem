/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_hud.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:02:50 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/27 16:43:49 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"
/*
static void	draw_timer_bubbles(t_index *index, t_gfx *gfx, int s)
{
	int	start_y = index->y - (55 * s);
	int	start_x = index->x + (10 * s);
	int x;
	int y;
	int	gfx_y;
	int	gfx_x;
	int	i = gfx->frame.bubble;

	while (13 - i)
	{
		y = start_y + (i % 4 * 13 * s);
		gfx_y = 0;
		while (gfx_y < 12)
		{
			x = start_x + (i % 3 * 13 * s);
			gfx_x = 0;
			while (gfx_x < 12)
			{
				if (gfx->sprite.bubble[gfx_y][gfx_x])
					pixel_put(gfx, x, y + (gfx->frame.timer % 2),
								gfx->sprite.bubble[gfx_y][gfx_x]);
				x += s;
				gfx_x++;
			}
			y += s;
			gfx_y++;
			gfx_x = 0;
		}
		i++;
	}
}

static int	draw_timer_bottle(t_index *index, t_gfx *gfx, int s)
{
	gfx->f = gfx->frame.timer;
	gfx->x = 0;
	gfx->y = 0;
	index->y = (MARGIN * s);
	index->x = (gfx->width - (60 * s) - (MARGIN * s));
	while ((gfx->y) < (90))
	{
		while ((gfx->x) < (60))
		{
			if (gfx->sprite.timer[gfx->f][gfx->y][gfx->x])
			{
				if (pixel_put(gfx, index->x, index->y,
						gfx->sprite.timer
						[gfx->f][gfx->y][gfx->x]) == ERROR)
					return (ERROR);
			}
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = ((gfx->width - (60 * s) - MARGIN * s));
		gfx->x = 0;
	}
	draw_timer_bubbles(index, gfx, s);
	return (0);
}

static int	draw_ammo(t_index *index, t_gfx *gfx, int s)
{

	gfx->f = gfx->frame.ammo;
	gfx->x = 0;
	gfx->y = 0;
	index->y = ((MARGIN * 2) * s);
	index->x = (gfx->width - (120 * s) - (MARGIN * s));

	while ((gfx->y) < (45))
	{
		while ((gfx->x) < (32))
		{
			if (gfx->sprite.ammo[gfx->f][gfx->y][gfx->x])
			{
				if (pixel_put(gfx, index->x, index->y,
						gfx->sprite.ammo
						[gfx->f][gfx->y][gfx->x]) == ERROR)
					return (ERROR);
			}
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = ((gfx->width - (120 * s) - MARGIN * s));
		gfx->x = 0;
	}

	return (0);
}

int	render_hud(t_index *index, t_gfx *gfx, int scale)
{
	if (draw_timer_bottle(index, gfx, scale) == ERROR)
		return (ERROR);
	if (draw_ammo(index, gfx, scale) == ERROR)
		return (ERROR);
	return (0);
}*/
