/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/25 12:52:48 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

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

static int	draw_test(t_gfx *gfx, int s)
{
	int y = 0;
	int x = 0;
	int width = 250;
	int i = 0;
	int i2 = 0;
	(void )s;
	while (i2 < 238)
	{
		while (i < 250)
		{
			printf("drawing: %d\n", gfx->animation.frames[0].pixels[x + (y * width)]);
			pixel_put(gfx, 150 + i, 150 + i2, gfx->animation.frames[0].pixels[x + (y * width)]);
			i++;
			x++;
		}
		i2++;
		y++;
		i = 0;
		x = 0;
	}

	return (0);
}

int	render_overlay(t_drown *d)
{
	draw_test(&d->gfx, d->gfx.scale);
	if (draw_right_arm(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (d->system.filters == TRUE)
		draw_color_filter(&d->gfx);
	if (d->gfx.frame.bubble >= 13)
		SDL_FillRect(d->gfx.screen, NULL, 0);
	if (render_hud(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (string_timeline(d) == ERROR)
		return (ERROR);
	if (d->system.filters == TRUE)
		draw_scanlines(&d->gfx);
	return (0);
}
