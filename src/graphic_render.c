/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:05:39 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/16 11:48:57 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

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
	cast->slice_height = (int)((SQUARE_SIZE + 90)
			/ cast->closest_coll * cast->plane_dist);
	cast->texture_yincrement
		= ((float)SQUARE_SIZE + 90) / (float)cast->slice_height;
	cast->texture_yoffset = 0;
	if (cast->slice_height > r->graph.height)
	{
		cast->texture_yoffset = (cast->slice_height - r->graph.height) / 2;
		cast->slice_height = r->graph.height + 90;
	}
	texture_y = (float)(cast->texture_yoffset * cast->texture_yincrement);
	location.start_x = ray_count;
	location.start_y = 0;
	location.end_y = r->graph.height;
	draw_column(r, location, texture_y);
}

static void	droplet(t_rain *r, int x, int y)
{
	pixel_put(&r->graph, x, y, 0xC1BCCB);
	pixel_put(&r->graph, x, y + 2, 0xC1BCCB);
	pixel_put(&r->graph, x, y + 4, 0xC1BCCB);
	pixel_put(&r->graph, x, y + 6, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 7, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 8, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 9, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 10, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 11, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 12, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 13, 0xD4D0DE);
}

static void	draw_overlay(t_rain *r)
{
	static int	y[24] = {10, 90, 50, 180, 80, 250, 140, 320, 220, 150,
		30, 40, 32, 450, 23, 53, 423, 54, 4, 12, 234, 123, 153, 231};
	static int	x[24] = {10, 90, 20, 80, 30, 70, 40, 60, 50, 110, 120,
		32, 323, 123, 431, 12, 43, 54, 76, 94, 37, 64, 12, 43};
	int			i;

	i = 0;
	while (i++ < 24)
		droplet(r, x[i], y[i]++);
	i = 0;
	while (i++ < 24)
	{
		if (y[i] >= 465)
		{
			y[i] = 0;
			x[i] = rand() % 639 + 1;
		}
	}
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
	draw_overlay(rain);
	if (draw_arraymap(rain) == ERROR)
		return (ERROR);
	if (SDL_UpdateWindowSurface(rain->graph.win) == ERROR)
		return (ERROR);
	return (0);
}
