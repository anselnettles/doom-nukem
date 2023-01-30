/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:05:39 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/30 15:22:49 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"
/*
//	Draws three distinct vertical lines on the graphical window's vertical
//	columns with the vline() tool.
//	The first line is considered the sky color (SKY_PRINT), the middle
//	the wall texture line, and bottom the ground (FLOOR_PRINT).
static void	draw_column(t_drown *d, t_location lo, float texture_y)
{
	if (d->graph.cast.slice_height < d->graph.height)
	{
		lo.end_y = (d->graph.height / 2) - (d->graph.cast.slice_height / 2);
		vline(d, lo, 0, SKY_PRINT);
		lo.start_y = lo.end_y + 1;
		lo.end_y += d->graph.cast.slice_height;
	}
	vline(d, lo, texture_y, 0);
	if (lo.end_y + 1 < d->graph.height)
	{
		lo.end_y++;
		lo.start_y = lo.end_y;
		lo.end_y = d->graph.height;
		vline(d, lo, 0, FLOOR_PRINT);
	}
}

//	There is a magic number (+90) used for applying a longer scale on the
//	otherwise cubic wall heights.
static void	column_render(t_drown *d, int ray_count)
{
	t_cast		*cast;
	t_location	location;
	float		texture_y;

	cast = &d->graph.cast;
	cast->slice_height = (int)((SQUARE_SIZE + 90)
			/ cast->closest_coll * cast->plane_dist);
	cast->texture_yincrement
		= ((float)SQUARE_SIZE + 90) / (float)cast->slice_height;
	cast->texture_yoffset = 0;
	if (cast->slice_height > d->graph.height)
	{
		cast->texture_yoffset = (cast->slice_height - d->graph.height) / 2;
		cast->slice_height = d->graph.height + 90;
	}
	texture_y = (float)(cast->texture_yoffset * cast->texture_yincrement);
	location.start_x = ray_count;
	location.start_y = 0;
	location.end_y = d->graph.height;
	draw_column(d, location, texture_y);
}

//	Beginning of drawing the three-dimensional space.
static int	draw_space(t_drown *d)
{
	int	ray_count;

	d->graph.cast.ray_angle = d->player.pos_angle + (FOV / 2);
	raycast_angle_check(&d->graph);
	ray_count = 0;
	while (ray_count < d->graph.width)
	{
		raycast(d, 100000, 100000);
		if (d->graph.cast.closest_coll > 0)
			column_render(d, ray_count);
		d->graph.cast.ray_angle -= d->graph.cast.degrees_per_ray;
		raycast_angle_check(&d->graph);
		ray_count++;
	}
	return (0);
}*/

//	Draws the user array map in the corner of the screen.
/*static void	draw_minimap(t_drown *d)
{
	d->graph.y = TOP_MARGIN;
	d->graph.x = MAP_MARGIN;
	d->index.x = 0;
	d->index.y = 0;
	while (d->index.y < (MAP_WIDTH / 2))
	{
		while (d->index.x < (MAP_WIDTH / 2))
		{
			draw_minimap_slot(d);
			d->index.x++;
			d->graph.x += 6;
		}
		d->index.x = 0;
		d->graph.x = MAP_MARGIN;
		d->index.y++;
		d->graph.y += 6;
	}
}*/

//	The graphical render order: Fill in black, draw the 3D space, draw the
//	array map in the window corner, update the window.

int	render(t_drown *data)
{
	//SDL_FillRect(data->gfx.screen, NULL, 0);
	//if (draw_space(drown) == ERROR)
	//	return (ERROR);
	//draw_overlay(drown);
	//draw_minimap(drown);
	//clear_screen(data);
	render_thread(data);
	draw_map(data);
	if (SDL_UpdateWindowSurface(data->gfx.window) == ERROR)
		return (ERROR);
	return (0);
}