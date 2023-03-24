/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:22:04 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/24 12:52:06 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"


void	toggle_lantern(t_drown *d)
{
	Mix_PlayChannel(0, d->audio.switch_flip, 0);
	if (d->gfx.lantern == LANTERN_OFF)
	{
		Mix_PlayChannel(1, d->audio.light_response, 0);
		d->gfx.lantern = TURN_ON;
	}
	else if (d->gfx.lantern == TRUE)
		d->gfx.lantern = LANTERN_OFF;
}

void	collect_airbottle(t_drown *d)
{
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	Mix_PlayChannel(2, d->audio.inhale, 0);
	d->gfx.frame.right_arm = 3;
}

int	player_object_collision(t_drown *d)
{
	if (d->map.map[(int)roundf(d->player.y / 64)]
		[(int)roundf(d->player.x / 64)][3] == 'Z')
		d->system.ending_state = REGULAR_ENDING;
	if (d->map.map[(int)roundf(d->player.y / 64)]
		[(int)roundf(d->player.x / 64)][3] == '$')
	{
		if (d->system.keyboard_state[SDL_SCANCODE_E])
		{
			d->map.map[(int)roundf(d->player.y / 64)]
			[(int)roundf(d->player.x / 64)][3] = '.';
			collect_airbottle(d);
		}
	}
	return (0);
}
