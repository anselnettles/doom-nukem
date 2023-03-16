/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/16 11:26:53 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	scale_window(t_gfx *gfx)
{
	if (gfx->scale == 1)
		gfx->scale = 2;
	else
		gfx->scale = 1;
	gfx->width = (WIDTH * gfx->scale);
	gfx->height = (HEIGHT * gfx->scale);
	SDL_SetWindowSize(gfx->window, gfx->width, gfx->height);
	gfx->screen = SDL_GetWindowSurface(gfx->window);
	gfx->centre = ((gfx->width / 2) / tan(30 * DEGREES));
}

int	quit_program(t_drown *d)
{
	Mix_FreeMusic(d->audio.main_menu);
	Mix_FreeMusic(d->audio.bluehole);
	Mix_FreeChunk(d->audio.inhale);
	Mix_FreeChunk(d->audio.timer_hit);
	SDL_FreeSurface(d->gfx.screen);
	SDL_DestroyWindow(d->gfx.window);
	Mix_Quit();
	exit(0);
	return (0);
}

void	deal_key(int key, t_drown *data)
{
	if (data->system.keyboard_state[SDL_SCANCODE_ESCAPE])
		data->system.play_state = EXIT;
	if (data->system.keyboard_state[SDL_SCANCODE_F1])
		scale_window(&data->gfx);
	if (key == SDLK_SPACE && data->player.in_air == 0)
	{
		data->player.velocity.y = 90.f;
		if (data->system.overlay_toggle == TRUE)
			data->player.in_air = 1;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_F2])
	{
		if (data->system.filters == TRUE)
			data->system.filters = FALSE;
		else
			data->system.filters = TRUE;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_F3])
		data->system.overlay_toggle = -data->system.overlay_toggle;
	if (data->system.keyboard_state[SDL_SCANCODE_F5]
		&& data->gfx.frame.bubble > 1)
		collect_airbottle(data);
	if (data->system.keyboard_state[SDL_SCANCODE_F])
			toggle_lantern(data);
}
