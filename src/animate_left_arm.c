/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_left_arm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:11 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/24 12:55:55 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	lantern_on_flicker(t_drown *d)
{
	static uint32_t	durtion = 0;

	if (d->system.time >= durtion)
		durtion++;
	if ((durtion >= 8 && durtion <= 9) || (durtion >= 11 && durtion <= 12)
		|| (durtion >= 15 && durtion <= 16) || (durtion >= 24 && durtion <= 126)
		|| (durtion >= 29 && durtion <= 31) || durtion >= 36)
		d->gfx.lantern = (TRUE + 0.1);
	else
		d->gfx.lantern = TURN_ON;
	if (durtion >= 130)
	{
		durtion = 0;
		d->gfx.lantern = TRUE;
	}
}

void	left_arm_loop(t_drown *d)
{
	if (d->gfx.lantern <= TURN_ON && d->gfx.lantern > TRUE)
	{
		lantern_on_flicker(d);
		Mix_PlayChannel(3, d->audio.light_hum, 0);
	}
}
