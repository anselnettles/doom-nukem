/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:49:19 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/16 15:41:13 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

float	ray_collision_distance(t_player *player, t_corf collision)
{
	float	distance;
	float	temp;

	temp = (float)((player->pos_x * player->pos_x) - \
			(2.0f * player->pos_x * collision.x) + \
			(collision.x * collision.x)) + \
			(float)((player->pos_y * player->pos_y) - \
			(2.0f * player->pos_y * collision.y) + \
			(collision.y * collision.y));
	distance = square_root(temp);
	return (distance);
}

int	find_hor_coll_point(t_rain *r)
{
	if (r->graph.cast.ray_angle > 0 && r->graph.cast.ray_angle < 180)
	{
		r->graph.cast.ray_y = (((int)r->player.pos_y >> 6) << 6) - 0.001f;
		r->graph.cast.ray_x = r->player.pos_x + \
			(r->player.pos_y - r->graph.cast.ray_y)
			/ tan(deg_to_rad(r->graph.cast.ray_angle));
		r->graph.cast.offset_y = -SQUARE_SIZE;
		r->graph.cast.offset_x = -r->graph.cast.offset_y
			/ tan(deg_to_rad(r->graph.cast.ray_angle));
	}
	else if (r->graph.cast.ray_angle > 180 && \
				r->graph.cast.ray_angle < 360)
	{
		r->graph.cast.ray_y = (((int)r->player.pos_y >> 6) << 6) + SQUARE_SIZE;
		r->graph.cast.ray_x = r->player.pos_x + \
			(r->player.pos_y - r->graph.cast.ray_y) / \
			tan(deg_to_rad(r->graph.cast.ray_angle));
		r->graph.cast.offset_y = SQUARE_SIZE;
		r->graph.cast.offset_x = -r->graph.cast.offset_y / \
			tan(deg_to_rad(r->graph.cast.ray_angle));
	}
	else
		return (0);
	return (1);
}

int	find_ver_coll_point(t_rain *r)
{
	if (r->graph.cast.ray_angle > 90 && r->graph.cast.ray_angle < 270)
	{
		r->graph.cast.ray_x = (((int)r->player.pos_x >> 6) << 6) - 0.001f;
		r->graph.cast.ray_y = r->player.pos_y + \
			(r->player.pos_x - r->graph.cast.ray_x) * \
			tan(deg_to_rad(r->graph.cast.ray_angle));
		r->graph.cast.offset_x = -SQUARE_SIZE;
		r->graph.cast.offset_y = -r->graph.cast.offset_x * \
			tan(deg_to_rad(r->graph.cast.ray_angle));
	}
	else if ((r->graph.cast.ray_angle > 270 && \
			r->graph.cast.ray_angle <= 360) || \
			(r->graph.cast.ray_angle >= 0 && r->graph.cast.ray_angle < 90))
	{
		r->graph.cast.ray_x = (((int)r->player.pos_x >> 6) << 6) + SQUARE_SIZE;
		r->graph.cast.ray_y = r->player.pos_y + \
			(r->player.pos_x - r->graph.cast.ray_x) * \
			tan(deg_to_rad(r->graph.cast.ray_angle));
		r->graph.cast.offset_x = SQUARE_SIZE;
		r->graph.cast.offset_y = -r->graph.cast.offset_x * \
			tan(deg_to_rad(r->graph.cast.ray_angle));
	}
	else
		return (0);
	return (1);
}

float	calculate_collision_distance(t_rain *r, int i, int measure, float dist)
{
	while (i < (measure / 2))
	{
		r->graph.cast.map_x = ((int)r->graph.cast.ray_x) >> 6;
		r->graph.cast.map_y = ((int)r->graph.cast.ray_y) >> 6;
		if (r->graph.cast.map_x >= 0 && r->graph.cast.map_x < r->index.width / 2
			&& r->graph.cast.map_y >= 0 && r->graph.cast.map_y < r->index.y / 2
			&& r->stage.grid[r->graph.cast.map_y][r->graph.cast.map_x] == '#')
		{
			if (measure == r->index.y)
				r->graph.cast.hor_coll_point_x = r->graph.cast.ray_x;
			else
				r->graph.cast.ver_coll_point_y = r->graph.cast.ray_y;
			r->corf.x = r->graph.cast.ray_x;
			r->corf.y = r->graph.cast.ray_y;
			dist = ray_collision_distance(&r->player, r->corf);
			return (dist);
		}
		else
		{
			r->graph.cast.ray_x += r->graph.cast.offset_x;
			r->graph.cast.ray_y += r->graph.cast.offset_y;
			i++;
		}
	}
	return (100000);
}

int	raycast(t_rain *r, float hor_coll_dist, float ver_coll_dist)
{
	if (find_hor_coll_point(r))
		hor_coll_dist = calculate_collision_distance(r, 0, r->index.y, 0);
	if (find_ver_coll_point(r))
		ver_coll_dist = calculate_collision_distance(r, 0, r->index.width, 0);
	if (ver_coll_dist < hor_coll_dist)
	{
		r->graph.cast.closest_coll = ver_coll_dist;
		r->graph.cast.texture_xoffset
			= (int)r->graph.cast.ver_coll_point_y % SQUARE_SIZE;
		if (r->graph.cast.ray_angle > 90 && r->graph.cast.ray_angle < 270)
			r->player.compass = WEST;
		else
			r->player.compass = EAST;
	}
	else
	{
		r->graph.cast.closest_coll = hor_coll_dist;
		r->graph.cast.texture_xoffset
			= (int)r->graph.cast.hor_coll_point_x % SQUARE_SIZE;
		if (r->graph.cast.ray_angle > 0 && r->graph.cast.ray_angle < 180)
			r->player.compass = NORTH;
		else
			r->player.compass = SOUTH;
	}
	return (0);
}
