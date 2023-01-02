/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/12/19 14:36:51 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static void	move_player(t_stage *stage, t_player *p, t_graph *g)
{

	if (g->e.key.keysym.sym == SDLK_w || g->e.key.keysym.sym == SDLK_UP)
	{
		if (stage->grid[p->collision.grid_pos_y] \
				[p->collision.grid_pos_x_plus_offset] == 0)
			p->pos_x += p->dir_x * p->move_speed;
		if (stage->grid[p->collision.grid_pos_y_plus_offset] \
				[p->collision.grid_pos_x] == 0)
			p->pos_y += p->dir_y * p->move_speed;
	}
	// if backwards
	// if left
	// if right
}

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
		if (r->graph.e.key.keysym.sym == SDLK_w || r->graph.e.key.keysym.sym == SDLK_UP
				|| r->graph.e.key.keysym.sym == SDLK_s || r->graph.e.key.keysym.sym == SDLK_DOWN
				|| r->graph.e.key.keysym.sym == SDLK_a || r->graph.e.key.keysym.sym == SDLK_LEFT
				|| r->graph.e.key.keysym.sym == SDLK_d || r->graph.e.key.keysym.sym == SDLK_RIGHT)
			move_player(&r->stage, &r->player, &r->graph);
		render(r);
	}
}
