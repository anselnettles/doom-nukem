/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_hud.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:02:50 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/06 14:23:15 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	draw_timer_bubbles(t_index *index, t_gfx *gfx, int s, int bubbles)
{
	index->y -= (55 * s);
	index->x += (10 * s);
	while (13 - bubbles)
	{
		index->y += (bubbles % 4 * 13 * s);
		gfx->y = 0;
		while (gfx->y < BUBBLE_HEIGHT)
		{
			index->x += (bubbles % 3 * 13 * s);
			gfx->x = 0;
			while (gfx->x < BUBBLE_WIDTH)
			{
				if (gfx->texture[BUBBLE].frame[0].pixels
					[gfx->x + (gfx->y * BUBBLE_WIDTH)])
					pixel_put(gfx, index->x, index->y + (gfx->frame.timer % 2),
						gfx->texture[BUBBLE].frame[0].pixels
					[gfx->x + (gfx->y * BUBBLE_WIDTH)]);
				index->x += s;
				gfx->x++;
			}
			index->y += s;
			gfx->y++;
		}
		bubbles++;
	}
}

static int	draw_timer_bottle(t_index *index, t_gfx *gfx, int s, int f)
{
	gfx->y = 0;
	index->y = (MARGIN * s);
	index->x = (gfx->width - (TIMER_WIDTH * s) - (MARGIN * s));
	while ((gfx->y) < (TIMER_HEIGHT))
	{
		gfx->x = 0;
		while ((gfx->x) < (TIMER_WIDTH))
		{
			if (gfx->texture[TIMER].frame[f].pixels
				[gfx->x + (gfx->y * TIMER_WIDTH)])
				if (pixel_put(gfx, index->x, index->y,
						gfx->texture[TIMER].frame[f].pixels
						[gfx->x + (gfx->y * TIMER_WIDTH)]) == ERROR)
					return (ERROR);
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = ((gfx->width - (TIMER_WIDTH * s) - MARGIN * s));
	}
	draw_timer_bubbles(index, gfx, s, gfx->frame.bubble);
	return (0);
}

static int	draw_ammo(t_index *index, t_gfx *gfx, int s, int f)
{
	gfx->y = 0;
	index->y = ((MARGIN * 2) * s);
	index->x = (gfx->width - ((MARGIN * 7) * s));
	while (gfx->y < AMMO_HEIGHT)
	{
		gfx->x = 0;
		while (gfx->x < AMMO_WIDTH)
		{
			if (gfx->texture[AMMO].frame[f].pixels
				[gfx->x + (gfx->y * AMMO_WIDTH)])
				if (pixel_put(gfx, index->x, index->y,
						gfx->texture[AMMO].frame[f].pixels
						[gfx->x + (gfx->y * AMMO_WIDTH)]) == ERROR)
					return (ERROR);
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = ((gfx->width - ((MARGIN * 7) * s)));
	}
	return (0);
}

int	render_hud(t_index *index, t_gfx *gfx, int scale)
{
	if (draw_timer_bottle(index, gfx, scale, gfx->frame.timer) == ERROR)
		return (ERROR);
	if (draw_ammo(index, gfx, scale, gfx->frame.ammo) == ERROR)
		return (ERROR);
	return (0);
}
