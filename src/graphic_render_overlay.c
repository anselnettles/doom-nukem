/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/16 11:21:42 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

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


static int	draw_right_arm(t_index *index, t_gfx *gfx, int s)
{
	gfx->f = gfx->frame.right_arm;
	gfx->x = 0;
	gfx->y = 0;
	index->y = ((gfx->height - (238 * s) + MARGIN * s) + gfx->shake_y * s);
	index->x = ((gfx->width - (250 * s) + MARGIN * s) + gfx->shake_x * s);
	while ((index->y) < (gfx->height))
	{
		while ((index->x) < (gfx->width))
		{
			if (gfx->sprite.right_arm[gfx->f][gfx->y][gfx->x])
				if (pixel_put(gfx, index->x, index->y,
						gfx->sprite.right_arm
						[gfx->f][gfx->y][gfx->x]) == ERROR)
					return (ERROR);
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = ((gfx->width - (250 * s) + MARGIN * s) + gfx->shake_x * s);
		gfx->x = 0;
	}
	return (0);
}

int	render_overlay(t_drown *d)
{
	if (draw_right_arm(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (d->system.color_filter == TRUE)
		draw_color_filter(&d->gfx);
	if (d->gfx.frame.bubble >= 13)
		SDL_FillRect(d->gfx.screen, NULL, 0);
	if (draw_timer_bottle(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (string_timeline(d) == ERROR)
		return (ERROR);
	if (d->system.scanline == TRUE)
		draw_scanlines(&d->gfx);
	return (0);
}
