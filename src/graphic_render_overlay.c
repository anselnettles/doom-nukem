/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/08 19:28:12 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int	draw_right_arm(t_index *index, t_gfx *gfx)
{
	gfx->f = gfx->frame.right_arm;
	gfx->x = 0;
	gfx->y = 0;
	index->y = ((gfx->height - (238 * gfx->scale) + MARGIN) + gfx->shake_y);
	index->x = ((gfx->width - (250 * gfx->scale) + MARGIN) + gfx->shake_x);
	while ((index->y) < (gfx->height))
	{
		while ((index->x) < (gfx->width))
		{
			if (gfx->sprite.right_arm[gfx->f][gfx->y][gfx->x])
				if (pixel_put(gfx, index->x, index->y,
						gfx->sprite.right_arm[gfx->f][gfx->y][gfx->x]) == ERROR)
					return (ERROR);
			index->x += gfx->scale;
			gfx->x++;
		}
		index->y += gfx->scale;
		gfx->y++;
		index->x = ((gfx->width - (250 * gfx->scale) + MARGIN) + gfx->shake_x);
		gfx->x = 0;
	}
	return (0);
}

int		render_overlay(t_drown *d)
{
	if (draw_right_arm(&d->index, &d->gfx) == ERROR)
		return (ERROR);
	return (0);
}
