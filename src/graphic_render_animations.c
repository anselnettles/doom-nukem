/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_animations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:28:04 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/19 14:50:41 by aviholai         ###   ########.fr       */
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

static void	timer_loop(t_drown *d)
{
	if (d->system.time % 1000 < 500)
		d->gfx.frame.ammo = 0;
	else
		d->gfx.frame.ammo = 1;
	if (d->system.time >= 0 && d->system.time < 20000)
	{
		if (d->system.time % 1000 < 500)
			d->gfx.frame.timer = 0;
		else
			d->gfx.frame.timer = 1;
	}
	if (d->system.time >= 20000 && d->system.time < 40000)
	{
		if (d->system.time % 1000 < 500)
			d->gfx.frame.timer = 2;
		else
			d->gfx.frame.timer = 3;
	}
	if (d->system.time >= 40000 && d->system.time < 60000)
	{
		if (d->system.time % 1000 < 500)
			d->gfx.frame.timer = 4;
		else
			d->gfx.frame.timer = 5;
	}
	if (d->system.time >= 60000)
	{
		if (d->system.time % 1000 < 500)
			d->gfx.frame.timer = 6;
		else
			d->gfx.frame.timer = 7;
	}
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

static void	flow_adjustment(t_drown *d)
{
	if (d->system.time % 2400 > 0 && d->system.time % 2400 < 600)
			d->gfx.flow_y_adjust = (d->system.time % 200 / 60);
}

int	animation_loop(t_drown *d)
{
	right_arm_loop(d);
	timer_loop(d);
	flow_adjustment(d);
	return (0);
}
