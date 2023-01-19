/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/19 16:25:58 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

static void	toggle_scale(t_rain *r)
{
	if (r->graph.scale == 1)
		r->graph.scale = 2;
	else
		r->graph.scale = 1;
	r->graph.width = (WIDTH * r->graph.scale);
	r->graph.height = (HEIGHT * r->graph.scale);
	SDL_SetWindowSize(r->graph.win, r->graph.width, r->graph.height);
	r->graph.surf = SDL_GetWindowSurface(r->graph.win);
	r->graph.cast.plane_dist = (double)(r->graph.width / 2)
		/ tan(deg_to_rad(FOV / 2));
	r->graph.cast.degrees_per_column = (double)r->graph.width / (double)FOV;
	r->graph.cast.degrees_per_ray = (double)FOV / (double)r->graph.width;
}

static void	quit_program(t_rain *r)
{
	SDL_FreeSurface(r->graph.texture[0]);
	SDL_FreeSurface(r->graph.texture[1]);
	SDL_FreeSurface(r->graph.texture[2]);
	SDL_FreeSurface(r->graph.texture[3]);
//	SDl_DestroyTexture();
	SDL_DestroyWindow(r->graph.win);
	(void)r;
	SDL_Quit();
	exit(0);
}

static void	keyboard_second_batch(t_rain *r, SDL_Keycode key)
{
	if (key == SDLK_ESCAPE)
		quit_program(r);
	if (key == SDLK_KP_PLUS)
		toggle_scale(r);
	if (key == SDLK_o)
	{
		if (r->graph.scanline == TRUE)
			r->graph.scanline = FALSE;
		else
			r->graph.scanline = TRUE;
	}
	if (key == SDLK_m)
	{
		if (r->graph.map == PLAYER_MAP)
			r->graph.map = DEV_MAP;
		else
			r->graph.map = PLAYER_MAP;
	}
}

void	keyboard_input(t_rain *r)
{
	SDL_Keycode	key;

	key = r->graph.e.key.keysym.sym;
	if (r->graph.e.type == SDL_KEYDOWN)
	{
		if (key == SDLK_w || key == SDLK_UP
			|| key == SDLK_s || key == SDLK_DOWN)
			move_forward_back(&r->editor, &r->player, key);
		if (key == SDLK_a || key == SDLK_LEFT
			|| key == SDLK_d || key == SDLK_RIGHT)
			move_turn(&r->player, key);
		keyboard_second_batch(r, key);
	}
}
