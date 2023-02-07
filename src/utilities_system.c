/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/07 16:31:16 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void	sdl_loop(t_drown *d)
{
	while (d->play_state == PLAY)
	{
		d->system.current_time = SDL_GetTicks();
		d->system.delta_time = (d->system.current_time - d->system.last_time);
		if ((d->system.current_time / 1000) >= d->system.second)
		{
				d->system.second++;
				d->index.i++;
		}
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
