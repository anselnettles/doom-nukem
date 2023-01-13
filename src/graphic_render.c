/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:05:39 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/12 15:50:30 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//	Draws three distinct vertical lines on the graphical window's vertical
//	columns with the vline() tool.
//	The first line is considered the sky color (SKY_PRINT), the middle
//	the wall texture line, and bottom the ground (FLOOR_PRINT).
static void	draw_column(t_rain *r, t_location lo, float texture_y)
{
	if (r->graph.cast.slice_height < r->graph.height)
	{
		lo.end_y = (r->graph.height / 2) - (r->graph.cast.slice_height / 2);
		vline(r, lo, 0, SKY_PRINT);
		lo.start_y = lo.end_y + 1;
		lo.end_y += r->graph.cast.slice_height;
	}
	vline(r, lo, texture_y, 0);
	if (lo.end_y + 1 < r->graph.height)
	{
		lo.end_y++;
		lo.start_y = lo.end_y;
		lo.end_y = r->graph.height;
		vline(r, lo, 0, FLOOR_PRINT);
	}
}

//	There is a magic number (+90) used for applying a longer scale on the
//	otherwise cubic wall heights.
static void	column_render(t_rain *r, int ray_count)
{
	t_cast		*cast;
	t_location	location;
	float		texture_y;

	cast = &r->graph.cast;
	cast->slice_height
		= ((float)SQUARE_SIZE + 90) / cast->closest_coll * cast->plane_dist;
	cast->texture_yincrement
		= ((float)SQUARE_SIZE + 90) / (float)cast->slice_height;
	cast->texture_yoffset = 0;
	if (cast->slice_height > r->graph.height)
	{
		cast->texture_yoffset = (cast->slice_height - r->graph.height) / 2;
		cast->slice_height = r->graph.height + 90;
	}
	texture_y = cast->texture_yoffset * cast->texture_yincrement;
	location.start_x = ray_count;
	location.start_y = 0;
	location.end_y = r->graph.height;
	draw_column(r, location, texture_y);
}

//	Beginning of drawing the three-dimensional space.
static int	draw_space(t_rain *r)
{
	int	ray_count;

	r->graph.cast.ray_angle = r->player.pos_angle + (FOV / 2);
	raycast_angle_check(&r->graph);
	ray_count = 0;
	while (ray_count < r->graph.width)
	{
		raycast(r);
		if (r->graph.cast.closest_coll > 0)
			column_render(r, ray_count);
		r->graph.cast.ray_angle -= r->graph.cast.degrees_per_ray;
		raycast_angle_check(&r->graph);
		ray_count++;
	}
	return (0);
}

//	Draws the user array map in the corner of the screen.
static int	draw_arraymap(t_rain *r)
{
	int	x;
	int	y;

	r->graph.y = TOP_MARGIN;
	r->graph.x = MAP_MARGIN;
	x = 1;
	y = 1;
	while (y <= r->index.y)
	{
		while (x <= r->index.width)
			x = draw_map_slot(r, x, y);
		x = 1;
		r->graph.x = MAP_MARGIN;
		y++;
		if (r->graph.map == PLAYER_MAP)
			y++;
		r->graph.y += 6;
	}
	return (0);
}

//	The graphical render order: Fill in black, draw the 3D space, draw the
//	array map in the window corner, update the window.
int	render(t_rain *rain)
{
	SDL_FillRect(rain->graph.surf, NULL, 0);
	if (draw_space(rain) == ERROR)
		return (ERROR);
	if (draw_arraymap(rain) == ERROR)
		return (ERROR);
	if (SDL_UpdateWindowSurface(rain->graph.win) == ERROR)
		return (ERROR);
	return (0);
}
