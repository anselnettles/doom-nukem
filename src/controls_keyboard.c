/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/05 14:21:37 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static void	move_forward_back(t_stage *stage, t_player *p, t_graph *g)
{
	if (g->e.key.keysym.sym == SDLK_w || g->e.key.keysym.sym == SDLK_UP)
	{
		if (stage->grid[p->collision.grid_pos_y] \
				[p->collision.grid_pos_x_plus_offset] == 0)
			p->pos_x += p->dir_x * (float)p->move_speed;
		if (stage->grid[p->collision.grid_pos_y_plus_offset] \
				[p->collision.grid_pos_x] == 0)
			p->pos_y += p->dir_y * (float)p->move_speed;
	}
	if (g->e.key.keysym.sym == SDLK_s || g->e.key.keysym.sym == SDLK_DOWN)
	{
		if (stage->grid[p->collision.grid_pos_y][p->collision.grid_pos_x_minus_offset] == 0)
			p->pos_x -= p->dir_x * (float)p->move_speed;
		if (stage->grid[p->collision.grid_pos_y_minus_offset][p->collision.grid_pos_x] == 0)
			p->pos_y -= p->dir_y * (float)p->move_speed;
	}
}

static void	move_turn(t_player *p, t_graph *g)
{
	if (g->e.key.keysym.sym == SDLK_a || g->e.key.keysym.sym == SDLK_LEFT)
	{
		p->pos_angle += TURN_SPEED;
		if (p->pos_angle >= 360)
			p->pos_angle -= 360;
		p->dir_x = (float)cos(deg_to_rad(p->pos_angle));
		p->dir_y = (float)-sin(deg_to_rad(p->pos_angle));
	}
	if (g->e.key.keysym.sym == SDLK_d || g->e.key.keysym.sym == SDLK_RIGHT)
	{
		p->pos_angle -= TURN_SPEED;
		if (p->pos_angle < 0)
			p->pos_angle += 360;
		p->dir_x = (float)cos(deg_to_rad(p->pos_angle));
		p->dir_y = (float)-sin(deg_to_rad(p->pos_angle));
	}
}

static void	toggle_scale(t_rain *r)
{
	if (r->graph.scale == 1)
		r->graph.scale = 2;
	else if (r->graph.scale == 2)
		r->graph.scale = 3;
	else
		r->graph.scale = 1;
	r->graph.width = (WIDTH * r->graph.scale);
	r->graph.height = (HEIGHT * r->graph.scale);
	SDL_SetWindowSize(r->graph.win, r->graph.width, r->graph.height);
	r->graph.surf = SDL_GetWindowSurface(r->graph.win);
	r->graph.raycast.plane_distance = (double)(r->graph.width / 2)
		/ tan(deg_to_rad(FOV / 2));
	r->graph.raycast.degrees_per_column = (double)r->graph.width / (double)FOV;
	r->graph.raycast.degrees_per_ray = (double)FOV / (double)r->graph.width;
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
		if (r->graph.e.key.keysym.sym == SDLK_ESCAPE)
			quit_program(r);
		if (r->graph.e.key.keysym.sym == SDLK_KP_PLUS)
			toggle_scale(r);
		if (r->graph.e.key.keysym.sym == SDLK_o)
		{
			if (r->graph.scanline == TRUE)
				r->graph.scanline = FALSE;
			else
				r->graph.scanline = TRUE;
		}
		if (r->graph.e.key.keysym.sym == SDLK_m)
		{
			if (r->graph.map == PLAYER_MAP)
				r->graph.map = DEV_MAP;
			else
				r->graph.map = PLAYER_MAP;
		}
		if (r->graph.e.key.keysym.sym == SDLK_w || r->graph.e.key.keysym.sym == SDLK_UP
				|| r->graph.e.key.keysym.sym == SDLK_s || r->graph.e.key.keysym.sym == SDLK_DOWN)
			move_forward_back(&r->stage, &r->player, &r->graph);
		if (r->graph.e.key.keysym.sym == SDLK_a || r->graph.e.key.keysym.sym == SDLK_LEFT
				|| r->graph.e.key.keysym.sym == SDLK_d || r->graph.e.key.keysym.sym == SDLK_RIGHT)
			move_turn(&r->player, &r->graph);
		render(r);
	}
}
