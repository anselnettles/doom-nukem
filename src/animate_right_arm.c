/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_right_arm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:28:04 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/06 16:50:36 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	x_right_arm_flail(t_gfx *gfx)
{
	if (gfx->shake_xtoggle == FALSE)
	{
		gfx->shake_x++;
		if (gfx->shake_x >= MARGIN)
			gfx->shake_xtoggle = TRUE;
	}
	else
	{
		gfx->shake_x--;
		if (gfx->shake_x <= -MARGIN)
			gfx->shake_xtoggle = FALSE;
	}
}

void	y_right_arm_flail(t_gfx *gfx)
{
	if (gfx->shake_ytoggle == FALSE)
	{
		gfx->shake_y += 0.5;
		if (gfx->shake_y >= (MARGIN / 2))
			gfx->shake_y++;
		if (gfx->shake_y >= MARGIN)
			gfx->shake_ytoggle = TRUE;
	}
	else
	{
		gfx->shake_y -= 0.5;
		if (gfx->shake_y <= (-MARGIN / 2))
			gfx->shake_y--;
		if (gfx->shake_y <= -MARGIN)
			gfx->shake_ytoggle = FALSE;
	}
}

void	right_arm_loop(t_drown *d)
{
	if (d->gfx.frame.right_arm != 3 && d->gfx.frame.right_arm != 4)
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
	else if (d->gfx.frame.right_arm == 3)
	{
		if (d->system.time % 800 > 0 && d->system.time % 800 < 400)
			d->gfx.frame.right_arm = 4;
	}
	else if (d->gfx.frame.right_arm == 4)
	{
		if (d->system.time % 800 > 400)
			d->gfx.frame.right_arm = 0;
	}
}
