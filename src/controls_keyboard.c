/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/12/19 12:29:40 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

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
}

static void	quit_program(t_rain *r)
{
	SDL_DestroyWindow(r->graph.win);
	SDL_Quit();
	exit(0);
}

void	keyboard(t_rain *r)
{
	if (r->graph.e.type == SDL_KEYDOWN)
	{
		write(1, ".", 1);
		if (r->graph.e.key.keysym.sym == ESC)
			quit_program(r);
		if (r->graph.e.key.keysym.sym == NUMPAD_MINUS)
			toggle_scale(r);
		if (r->graph.e.key.keysym.sym == SDLK_m)
		{
			if (r->graph.map == PLAYER_MAP)
				r->graph.map = DEV_MAP;
			else
				r->graph.map = PLAYER_MAP;
		}
		if (r->graph.e.key.keysym.sym == SDLK_w || r->graph.e.key.keysym.sym == SDLK_UP)
			r->player.where.z++;
		if (r->graph.e.key.keysym.sym == SDLK_s || r->graph.e.key.keysym.sym == SDLK_DOWN)
			r->player.where.z--;
		render(r);
	}
}
