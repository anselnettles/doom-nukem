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

void	raycast_angle_check(t_graph *graph)
{
	if (graph->cast.ray_angle >= 360)
		graph->cast.ray_angle -= 360;
	else if (graph->cast.ray_angle < 0)
		graph->cast.ray_angle += 360;
}

static void	collision_check(t_player *p)
{
	int	x_offset;
	int	y_offset;

	if (p->dir_x < 0)
		x_offset = -15;
	else
		x_offset = 15;
	if (p->dir_y < 0)
		y_offset = -15;
	else
		y_offset = 15;
	p->collision.loc_x = (p->pos_x / 64);
	p->collision.loc_x_pos_offset = ((p->pos_x + x_offset) / 64);
	p->collision.loc_x_neg_offset = ((p->pos_x - x_offset) / 64);
	p->collision.loc_y = (p->pos_y / 64);
	p->collision.loc_y_pos_offset = ((p->pos_y + y_offset) / 64);
	p->collision.loc_y_neg_offset = ((p->pos_y - y_offset) / 64);
}

void	move_forward_back(t_stage *stage, t_player *p, SDL_Keycode key)
{
	collision_check(p);
	if (key == SDLK_w || key == SDLK_UP)
	{
		if (stage->grid[p->collision.loc_y][p->collision.loc_x_pos_offset] != '#')
			p->pos_x += p->dir_x * (float)p->move_speed;
		if (stage->grid[p->collision.loc_y_pos_offset][p->collision.loc_x] != '#')
			p->pos_y += p->dir_y * (float)p->move_speed;
	}
	if (key == SDLK_s || key == SDLK_DOWN)
	{
		if (stage->grid[p->collision.loc_y][p->collision.loc_x_neg_offset] != '#')
			p->pos_x -= p->dir_x * (float)p->move_speed;
		if (stage->grid[p->collision.loc_y_neg_offset][p->collision.loc_x] != '#')
			p->pos_y -= p->dir_y * (float)p->move_speed;
	}
}

void	move_turn(t_player *p, SDL_Keycode key)
{
	if (key == SDLK_a || key == SDLK_LEFT)
		p->pos_angle += TURN_SPEED;
	if (key == SDLK_d || key == SDLK_RIGHT)
		p->pos_angle -= TURN_SPEED;
	if (p->pos_angle >= 360)
		p->pos_angle -= 360;
	if (p->pos_angle < 0)
		p->pos_angle += 360;
	p->dir_x = (float)cos(deg_to_rad(p->pos_angle));
	p->dir_y = (float)-sin(deg_to_rad(p->pos_angle));
}
