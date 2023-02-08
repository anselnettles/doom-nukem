/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_animations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:28:04 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/08 10:45:53 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	x_right_arm_flail(t_gfx *gfx)
{
		if (gfx->shake_toggle == FALSE)
		{
			gfx->shake_x++;
			if (gfx->shake_x >= MARGIN)
				gfx->shake_toggle = TRUE;
		}
		else
		{
			gfx->shake_x--;
			if (gfx->shake_x <= -MARGIN)
				gfx->shake_toggle = FALSE;
		}
}

void	y_right_arm_flail(t_gfx *gfx)
{
	if ((gfx->shake_x <= -MARGIN / 2) || (gfx->shake_x > MARGIN / 2))
		gfx->shake_y++;
	else if ((gfx->shake_x > -MARGIN / 2) || (gfx->shake_x <= -MARGIN / 2))
		gfx->shake_y--;
}

static void	right_arm_loop(t_drown *d)
{
	if (d->system.time % 600 > 0 && d->system.time % 600 < 600)
		d->gfx.frame.right_arm = 1;
	if (d->system.time % 1200 > 0 && d->system.time % 1200 < 600)
		d->gfx.frame.right_arm = 2;
	if (d->system.time % 1800 > 0 && d->system.time % 1800 < 600)
		d->gfx.frame.right_arm = 1;
	if (d->system.time % 2400 > 0 && d->system.time % 2400 < 600)
		d->gfx.frame.right_arm = 0;
}

int			animation_loop(t_drown *d)
{
	right_arm_loop(d);
	return (0);
}
