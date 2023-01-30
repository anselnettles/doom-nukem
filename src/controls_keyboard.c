/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 17:36:13 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	toggle_scale(t_drown *d)
{
	if (d->gfx.scale == 1)
		d->gfx.scale = 2;
	else
		d->gfx.scale = 1;
	//d->graph.width = (WIDTH * d->graph.scale);
	//d->graph.height = (HEIGHT * d->graph.scale);
	//SDL_SetWindowSize(d->graph.win, d->graph.width, d->graph.height);
	//d->graph.surf = SDL_GetWindowSurface(d->graph.win);
	//d->graph.cast.plane_dist = (double)(d->graph.width / 2)
	//	/ tan(deg_to_rad(FOV / 2));
	//d->graph.cast.degrees_per_column = (double)d->graph.width / (double)FOV;
	//d->graph.cast.degrees_per_ray = (double)FOV / (double)d->graph.width;

	//RETURN TO INITIALIZE_MEDIA() INSTEAD?
}

static void	quit_program(t_drown *d)
{
	SDL_FreeSurface(d->gfx.texture[0]);
	SDL_FreeSurface(d->gfx.texture[1]);
	SDL_FreeSurface(d->gfx.texture[2]);
	SDL_FreeSurface(d->gfx.texture[3]);
	SDL_DestroyWindow(d->gfx.win);
	(void)d;
	SDL_Quit();
	exit(0);
}

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

	key = d->gfx.e.key.keysym.sym;
	if (d->gfx.e.type == SDL_KEYDOWN)
	{
		if (key == SDLK_w || key == SDLK_UP
			|| key == SDLK_s || key == SDLK_DOWN)
			move_forward_back(&d->editor, &d->player, key);
		if (key == SDLK_a || key == SDLK_LEFT
			|| key == SDLK_d || key == SDLK_RIGHT)
			move_turn(&d->player, key);
		keyboard_second_batch(d, key);
	}
	if (d->gfx.e.window.event == SDL_WINDOWEVENT_CLOSE)
		quit_program(d);
}
