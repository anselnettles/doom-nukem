/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_hud.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:28:04 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/06 16:50:53 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	hud_animation_loop(t_drown *d)
{
	if (d->system.time % 1000 < 500)
	{
		if (d->system.time >= 0 && d->system.time < 20000)
			d->gfx.frame.timer = 0;
		else if (d->system.time >= 20000 && d->system.time < 40000)
			d->gfx.frame.timer = 2;
		else if (d->system.time >= 40000 && d->system.time < 60000)
			d->gfx.frame.timer = 4;
		else if (d->system.time >= 60000)
			d->gfx.frame.timer = 6;
		d->gfx.frame.ammo = 0;
	}
	else
	{
		if (d->system.time >= 0 && d->system.time < 20000)
			d->gfx.frame.timer = 1;
		else if (d->system.time >= 20000 && d->system.time < 40000)
			d->gfx.frame.timer = 3;
		else if (d->system.time >= 40000 && d->system.time < 60000)
			d->gfx.frame.timer = 5;
		else if (d->system.time >= 60000)
			d->gfx.frame.timer = 7;
		d->gfx.frame.ammo = 1;
	}
}

void	overworld_sprite_loop(t_drown *d)
{
	if (d->system.time % 1000 > 0 && d->system.time % 1000 < 250)
	{
		d->gfx.frame.bottle = 0;
		if (d->gfx.frame.algae <= 0)
			d->gfx.frame.algae++;
	}
	if ((d->system.time % 1000 >= 250 && d->system.time % 1000 < 500)
		|| (d->system.time % 1000 >= 750 && d->system.time % 1000 < 1000))
		d->gfx.frame.bottle = 1;
	if (d->system.time % 1000 >= 500 && d->system.time % 1000 < 750)
	{
		d->gfx.frame.bottle = 2;
		if (d->gfx.frame.algae >= 1)
			d->gfx.frame.algae--;
	}
}

void	flow_adjustment(t_drown *d)
{
	if (d->system.time % 2400 > 0 && d->system.time % 2400 < 600)
			d->gfx.flow_y_adjust = (d->system.time % 200 / 60);
	if (d->system.time % 600 >= 0 && d->system.time % 600 < 200)
		d->gfx.frame.transition = 0;
	else if (d->system.time % 600 >= 200 && d->system.time % 600 < 400)
		d->gfx.frame.transition = 1;
	else if (d->system.time % 600 >= 400 && d->system.time % 600 <= 600)
		d->gfx.frame.transition = 2;
}
