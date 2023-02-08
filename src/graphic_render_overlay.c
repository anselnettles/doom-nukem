/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/08 13:08:14 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	draw_right_arm(t_drown *d)
{
	int	f;
	int	y;
	int	x;

	f = d->gfx.frame.right_arm;
	y = 0;
	x = 0;
	d->index.y = ((d->gfx.height - 238 + MARGIN) + d->gfx.shake_y);
	d->index.x = ((d->gfx.width - 250 + MARGIN) + d->gfx.shake_x);
	while (d->index.y < d->gfx.height)
	{
		while (d->index.x < (d->gfx.width - 2))
		{
			if (d->gfx.sprite.right_arm[f][y][x])
				pixel_put(&d->gfx, d->index.x, d->index.y,
						d->gfx.sprite.right_arm[f][y][x]);
			d->index.x++;
			x++;
		}
		d->index.y++;
		y++;
		d->index.x = ((d->gfx.width - 250 + MARGIN) + d->gfx.shake_x);
		x = 0;
	}
}

int		render_overlay(t_drown *d)
{
	draw_right_arm(d);
	return (0);
}
