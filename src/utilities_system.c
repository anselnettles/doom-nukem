/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/07 19:37:05 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	animations(t_drown *d)
{
	if (d->system.current_time % 600 > 0 && d->system.current_time % 600 < 600)
		d->gfx.frame.right_arm = 1;
	if (d->system.current_time % 1200 > 0 && d->system.current_time % 1200 < 600)
		d->gfx.frame.right_arm = 2;
	if (d->system.current_time % 1800 > 0 && d->system.current_time % 1800 < 600)
		d->gfx.frame.right_arm = 1;
	if (d->system.current_time % 2400 > 0 && d->system.current_time % 2400 < 600)
		d->gfx.frame.right_arm = 0;
}

static void	track_time(t_drown *d)
{
		d->system.current_time = SDL_GetTicks();
		d->system.delta_time = (d->system.current_time - d->system.last_time);
		if ((d->system.current_time / 1000) >= d->system.second)
				d->system.second++;
		animations(d);
}

//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void		sdl_loop(t_drown *d)
{
	while (d->play_state == PLAY)
	{
		track_time(d);
		while (SDL_PollEvent(&d->event) != 0)
		{
			if (d->event.type == SDL_QUIT)
				d->play_state = EXIT;
			else if (d->event.type == SDL_KEYDOWN)
				deal_key(d->event.key.keysym.sym, d);
			else if (d->event.type == SDL_MOUSEMOTION)
				deal_mouse(d);
		}
		if (d->system.delta_time)
		{
			render(d);
			d->system.last_time = d->system.current_time;
		}
	}
}
