/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/08 16:08:49 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
static void	keyboard_second_batch(t_drown *d, SDL_Keycode key)
{
	if (key == SDLK_ESCAPE)
		quit_program(d);
	if (key == SDLK_KP_PLUS)
		toggle_scale(d);
	if (key == SDLK_o)
	{
		if (d->gfx.scanline == TRUE)
			d->gfx.scanline = FALSE;
		else
			d->gfx.scanline = TRUE;
	}
	if (key == SDLK_m)
	{
		//if (d->gfx.map == PLAYER_MAP)
		//	d->gfx.map = DEV_MAP;
		//else
		//	d->gfx.map = PLAYER_MAP;
	}
}

void	keyboard_input(t_drown *d)
{
	SDL_Keycode	key;

	key = d->event.key.keysym.sym;
	if (d->event.type == SDL_KEYDOWN)
	{
		if (key == SDLK_w || key == SDLK_UP
			|| key == SDLK_s || key == SDLK_DOWN)
			move_forward_back(&d->editor, &d->player, key);
		if (key == SDLK_a || key == SDLK_LEFT
			|| key == SDLK_d || key == SDLK_RIGHT)
			move_turn(&d->player, key);
		keyboard_second_batch(d, key);
	}
	if (d->event.window.event == SDL_WINDOWEVENT_CLOSE)
		quit_program(d);
}*/
