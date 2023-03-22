/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_left_arm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:11 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/22 14:41:06 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	lantern_on_flicker(t_drown *d)
{
	static uint32_t	duration = 0;

	if (d->system.time >= duration)
		duration++;
	printf("duration: %d \n", duration);
	if (duration >= 20)
	{
		duration = 0;
		d->gfx.lantern = TRUE;
	}
}

void	left_arm_loop(t_drown *d)
{
	if (d->gfx.lantern == TURN_ON)
		lantern_on_flicker(d);
}
