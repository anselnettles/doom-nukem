/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/16 14:58:27 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void		scale_window(t_gfx *gfx)
{
	if (gfx->scale == 1)
		gfx->scale = 2;
	else
		gfx->scale = 1;
	gfx->width = (WIDTH * gfx->scale);
	gfx->height = (HEIGHT * gfx->scale);
	SDL_SetWindowSize(gfx->window, gfx->width, gfx->height);
	gfx->screen = SDL_GetWindowSurface(gfx->window);
	gfx->dop = gfx->width / 2 / tan(30 * DEGREES);
}

static void	track_time(t_drown *d)
{
		d->system.time = SDL_GetTicks();
		d->system.delta_time = (d->system.time - d->system.last_time);
		if ((d->system.time / 1000) >= d->system.second)
				d->system.second++;
		if ((d->system.second / 5 >= d->system.five_second)
				&& (d->gfx.frame.bubble < 13))
		{
			d->system.five_second++;
			d->gfx.frame.bubble++;
		}
		d->system.frame_time = d->system.delta_time / 100.f;
		//printf("frame_time = %f\n", d->system.frame_time);
		animation_loop(d);
}

void	delta_time_move(t_drown *data)
{
		data->player.x -= 50.f * data->system.frame_time * data->player.dx;
		data->player.y -= 50.f * data->system.frame_time * data->player.dy;
}

//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void		sdl_loop(t_drown *d)
{
	d->system.keyboard_state = SDL_GetKeyboardState(NULL);
	while (d->system.play_state == PLAY)
	{
		track_time(d);
		while (SDL_PollEvent(&d->event) != 0)
		{
			if (d->event.type == SDL_QUIT)
				d->system.play_state = EXIT;
			else if (d->event.type == SDL_KEYDOWN)
				deal_key(d->event.key.keysym.sym, d);
			else if (d->event.type == SDL_MOUSEMOTION)
				deal_mouse(d);
			if (d->event.type == SDL_KEYDOWN || d->event.type == SDL_MOUSEMOTION)
				x_right_arm_flail(&d->gfx);
		}
		/*if (d->system.keyboard_state[SDL_SCANCODE_W])
			delta_time_move(d);*/
		move_player(d);
		strife(d);
		if (d->system.frame_time < 16.6666f)			//OPTIMOI MINUT
		{
			SDL_Delay(16.6666f - d->system.frame_time);
		}
			render(d);
			d->system.last_time = d->system.time;
		
	}
}
