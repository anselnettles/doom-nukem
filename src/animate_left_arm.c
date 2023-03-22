/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_left_arm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:11 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/22 15:11:30 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	lantern_on_flicker(t_drown *d)
{
	static uint32_t	duration = 0;

	if (d->system.time >= duration)
		duration++;
	if ((duration >= 2 && duration <= 3) || (duration >= 5 && duration <= 6)
		|| (duration >= 8 && duration <= 9) || (duration >= 12 && duration <= 13)
			|| (duration >= 14 && duration <= 16) || duration >= 17)
		d->gfx.lantern = (TRUE + 0.1);
	else
		d->gfx.lantern = TURN_ON;
	if (duration >= 130)
	{
		duration = 0;
		d->gfx.lantern = TRUE;
	}
}

void	left_arm_loop(t_drown *d)
{
	if (d->gfx.lantern <= TURN_ON && d->gfx.lantern > TRUE)
		lantern_on_flicker(d);
}
