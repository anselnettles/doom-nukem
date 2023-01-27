/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:49:19 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 17:41:23 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

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

static int	scan_horizontal_collision_point(t_drown *d)
{
	if (d->graph.cast.ray_angle > 0 && d->graph.cast.ray_angle < 180)
	{
		d->graph.cast.ray_y = (((int)d->player.pos_y >> 6) << 6) - 0.001f;
		d->graph.cast.ray_x
			= d->player.pos_x + (d->player.pos_y - d->graph.cast.ray_y)
			/ tan(deg_to_rad(d->graph.cast.ray_angle));
		d->graph.cast.offset_y = -SQUARE_SIZE;
		d->graph.cast.offset_x = -d->graph.cast.offset_y
			/ tan(deg_to_rad(d->graph.cast.ray_angle));
	}
	else if (d->graph.cast.ray_angle > 180 && d->graph.cast.ray_angle < 360)
	{
		d->graph.cast.ray_y = (((int)d->player.pos_y >> 6) << 6) + SQUARE_SIZE;
		d->graph.cast.ray_x
			= d->player.pos_x + (d->player.pos_y - d->graph.cast.ray_y)
			/ tan(deg_to_rad(d->graph.cast.ray_angle));
		d->graph.cast.offset_y = SQUARE_SIZE;
		d->graph.cast.offset_x = -d->graph.cast.offset_y
			/ tan(deg_to_rad(d->graph.cast.ray_angle));
	}
	else
		return (0);
	return (1);
}

static int	scan_vertical_collision_point(t_drown *d)
{
	if (d->graph.cast.ray_angle > 90 && d->graph.cast.ray_angle < 270)
	{
		d->graph.cast.ray_x = (((int)d->player.pos_x >> 6) << 6) - 0.001f;
		d->graph.cast.ray_y
			= d->player.pos_y + (d->player.pos_x - d->graph.cast.ray_x)
			* tan(deg_to_rad(d->graph.cast.ray_angle));
		d->graph.cast.offset_x = -SQUARE_SIZE;
		d->graph.cast.offset_y = -d->graph.cast.offset_x
			* tan(deg_to_rad(d->graph.cast.ray_angle));
	}
	else if ((d->graph.cast.ray_angle > 270
			&& d->graph.cast.ray_angle <= 360)
		|| (d->graph.cast.ray_angle >= 0 && d->graph.cast.ray_angle < 90))
	{
		d->graph.cast.ray_x = (((int)d->player.pos_x >> 6) << 6) + SQUARE_SIZE;
		d->graph.cast.ray_y = d->player.pos_y
			+ (d->player.pos_x - d->graph.cast.ray_x)
			* tan(deg_to_rad(d->graph.cast.ray_angle));
		d->graph.cast.offset_x = SQUARE_SIZE;
		d->graph.cast.offset_y = -d->graph.cast.offset_x
			* tan(deg_to_rad(d->graph.cast.ray_angle));
	}
	else
		return (0);
	return (1);
}

float	calculate_collision_distance(t_drown *d, int i, int toggle, float dist)
{
	while (i < (MAP_WIDTH / 2))
	{
		d->graph.cast.mapx = ((int)d->graph.cast.ray_x) >> 6;
		d->graph.cast.mapy = ((int)d->graph.cast.ray_y) >> 6;
		if (d->graph.cast.mapx >= 0 && d->graph.cast.mapx < (MAP_WIDTH) / 2
			&& d->graph.cast.mapy >= 0 && d->graph.cast.mapy < (MAP_WIDTH) / 2
			&& d->editor.map[d->graph.cast.mapy][d->graph.cast.mapx][0] == '#')
		{
			if (toggle)
				d->graph.cast.hor_coll_point_x = d->graph.cast.ray_x;
			else
				d->graph.cast.ver_coll_point_y = d->graph.cast.ray_y;
			d->corf.x = d->graph.cast.ray_x;
			d->corf.y = d->graph.cast.ray_y;
			dist = ray_collision_distance(&d->player, d->corf);
			return (dist);
		}
		else
		{
			d->graph.cast.ray_x += d->graph.cast.offset_x;
			d->graph.cast.ray_y += d->graph.cast.offset_y;
			i++;
		}
	}
	return (100000);
}

int	raycast(t_drown *d, float hor_coll_dist, float ver_coll_dist)
{
	if (scan_horizontal_collision_point(d))
		hor_coll_dist = calculate_collision_distance(d, 0, HORIZONTAL, 0);
	if (scan_vertical_collision_point(d))
		ver_coll_dist = calculate_collision_distance(d, 0, VERTICAL, 0);
	if (ver_coll_dist < hor_coll_dist)
	{
		d->graph.cast.closest_coll = ver_coll_dist;
		d->graph.cast.texture_xoffset
			= (int)d->graph.cast.ver_coll_point_y % SQUARE_SIZE;
		if (d->graph.cast.ray_angle > 90 && d->graph.cast.ray_angle < 270)
			d->player.compass = WEST;
		else
			d->player.compass = EAST;
	}
	else
	{
		d->graph.cast.closest_coll = hor_coll_dist;
		d->graph.cast.texture_xoffset
			= (int)d->graph.cast.hor_coll_point_x % SQUARE_SIZE;
		if (d->graph.cast.ray_angle > 0 && d->graph.cast.ray_angle < 180)
			d->player.compass = NORTH;
		else
			d->player.compass = SOUTH;
	}
	return (0);
}
