/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/12 15:41:35 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"


void	raycast_angle_check(t_graph *g)
{
	if (g->cast.ray_angle >= 360)
		g->cast.ray_angle -= 360;
	else if (g->cast.ray_angle < 0)
		g->cast.ray_angle += 360;
}

void	move_forward_back(t_stage *stage, t_player *p, t_graph *g)
{
	if (g->e.key.keysym.sym == SDLK_w || g->e.key.keysym.sym == SDLK_UP)
	{
		if (stage->grid[p->collision.loc_y][p->collision.loc_x_pos_offset] != '#')
			p->pos_x += p->dir_x * (float)p->move_speed;
		if (stage->grid[p->collision.loc_y_pos_offset][p->collision.loc_x] != '#')
			p->pos_y += p->dir_y * (float)p->move_speed;
	}
	if (g->e.key.keysym.sym == SDLK_s || g->e.key.keysym.sym == SDLK_DOWN)
	{
		if (stage->grid[p->collision.loc_y][p->collision.loc_x_neg_offset] != '#')
			p->pos_x -= p->dir_x * (float)p->move_speed;
		if (stage->grid[p->collision.loc_y_neg_offset][p->collision.loc_x] != '#')
			p->pos_y -= p->dir_y * (float)p->move_speed;
	}
}

void	collision_check(t_player *p)
{
	int	x_offset;
	int	y_offset;

	x_offset = 0;
	y_offset = 0;
	if (p->dir_x < 0)
		x_offset = -15;
	else
		x_offset = 15;
	if (p->dir_y < 0)
		y_offset = -15;
	else
		y_offset = 15;
	p->collision.loc_x = p->pos_x / 64;
	p->collision.loc_x_pos_offset = (p->pos_x + x_offset) / 64;
	p->collision.loc_x_neg_offset = (p->pos_x - x_offset) / 64;
	p->collision.loc_y = p->pos_y / 64;
	p->collision.loc_y_pos_offset = (p->pos_y + y_offset) / 64;
	p->collision.loc_y_neg_offset = (p->pos_y - y_offset) / 64;
}


void	move_turn(t_player *p, t_graph *g)
{
	if (g->e.key.keysym.sym == SDLK_a || g->e.key.keysym.sym == SDLK_LEFT)
	{
		p->pos_angle += TURN_SPEED;
		if (p->pos_angle >= 360)
			p->pos_angle = 0;
		p->dir_x = (float)cos(deg_to_rad(p->pos_angle));
		p->dir_y = (float)-sin(deg_to_rad(p->pos_angle));
	}
	if (g->e.key.keysym.sym == SDLK_d || g->e.key.keysym.sym == SDLK_RIGHT)
	{
		p->pos_angle -= TURN_SPEED;
		if (p->pos_angle < 0)
			p->pos_angle = 359;
		p->dir_x = (float)cos(deg_to_rad(p->pos_angle));
		p->dir_y = (float)-sin(deg_to_rad(p->pos_angle));
	}
}
