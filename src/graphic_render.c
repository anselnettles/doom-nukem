/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:05:39 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/05 16:04:32 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static void	draw_column(t_rain *r, t_coor start, t_coor end)
{
	if (r->graph.raycast.slice_height < r->graph.height)
	{
		r->graph.top_color = SKY_PRINT;
		r->graph.middle_color = SKY_PRINT;
		r->graph.bottom_color = SKY_PRINT >> 1;

		end.y = (r->graph.height / 2) - (r->graph.raycast.slice_height / 2);
		vline(&r->graph, start.x, start.y, end.y);
		start.y = end.y + 1;
		end.y += r->graph.raycast.slice_height;
	}

	r->graph.top_color = (WALL_PRINT << 6);
	r->graph.middle_color = WALL_PRINT;
	r->graph.bottom_color = (WALL_PRINT << 8);
	start.y -= (150 * r->graph.scale);
	vline(&r->graph, start.x, start.y, end.y);

	if (end.y + 1 < r->graph.height)
	{
		r->graph.top_color = FLOOR_PRINT >> 1;
		r->graph.middle_color = FLOOR_PRINT;
		r->graph.bottom_color = FLOOR_PRINT;

		end.y++;
		vline(&r->graph, start.x, end.y, r->graph.height);
	}
}

void	column_render(t_rain *r, int ray_count)
{
	t_raycast	*raycast;
	t_coor	start;
	t_coor	end;

//	printf("\n//Column() ClosestCollDist: %f \n", r->graph.raycast.closest_coll_dist);
//	printf("//Column() DistToProjPlane: %f \n", r->graph.raycast.plane_distance);

	raycast = &r->graph.raycast;
	raycast->slice_height = (float)SQUARE_SIZE / raycast->closest_coll_dist * raycast->plane_distance;
//	printf("//Column() ProjSliceHeight: %d \n", r->graph.raycast.slice_height);

	if (raycast->slice_height > r->graph.height)
		raycast->slice_height = r->graph.height;
	start.x = ray_count;
	start.y = 0;
	end.x = ray_count;
	end.y = r->graph.height;
	draw_column(r, start, end);
}

float	ray_collision_distance(t_player *player, t_coor collision)
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
	if (r->graph.raycast.ray_angle > 0 && r->graph.raycast.ray_angle < 180)
	{
		r->graph.raycast.ray_y = (((int)r->player.pos_y >> 6) << 6) - 0.001f;
		r->graph.raycast.ray_x = r->player.pos_x + \
			(r->player.pos_y - r->graph.raycast.ray_y) / \
			tan(deg_to_rad(r->graph.raycast.ray_angle));
		r->graph.raycast.offset_y = -SQUARE_SIZE;
		r->graph.raycast.offset_x = -r->graph.raycast.offset_y / tan(deg_to_rad(r->graph.raycast.ray_angle));
	}
	else if (r->graph.raycast.ray_angle > 180 && \
				r->graph.raycast.ray_angle < 360)
	{
		r->graph.raycast.ray_y = (((int)r->player.pos_y >> 6) << 6) + SQUARE_SIZE;
		r->graph.raycast.ray_x = r->player.pos_x + \
			(r->player.pos_y - r->graph.raycast.ray_y) / \
			tan(deg_to_rad(r->graph.raycast.ray_angle));
		r->graph.raycast.offset_y = SQUARE_SIZE;
		r->graph.raycast.offset_x = -r->graph.raycast.offset_y / \
			tan(deg_to_rad(r->graph.raycast.ray_angle));
	}
	else
		return (0);
	return (1);
}

float	calc_hor_coll_dist(t_rain *r)
{
	int		index;
	float	distance;

	index = 0;
	while (index < (r->index.y / 2))
	{
		r->graph.raycast.map_x = ((int)r->graph.raycast.ray_x) >> 6;
		r->graph.raycast.map_y = ((int)r->graph.raycast.ray_y) >> 6;
		if (r->graph.raycast.map_x >= 0 && r->graph.raycast.map_x < (r->index.width / 2)
				&& r->graph.raycast.map_y >= 0 && r->graph.raycast.map_y < (r->index.y / 2)
				&& r->stage.grid[r->graph.raycast.map_y][r->graph.raycast.map_x] == '#')
		{
			r->graph.raycast.hor_coll_point_x = r->graph.raycast.ray_x;
			r->coor.x = r->graph.raycast.ray_x;
			r->coor.y = r->graph.raycast.ray_y;
			distance = ray_collision_distance(&r->player, r->coor);
			return (distance);
		}
		else
		{
			r->graph.raycast.ray_x += r->graph.raycast.offset_x;
			r->graph.raycast.ray_y += r->graph.raycast.offset_y;
			index++;
		}
	}
	return (100000);
}

void	save_horizontal(t_rain *r, float hor_coll_dist)
{
	r->graph.raycast.closest_coll_dist = hor_coll_dist;
	r->graph.raycast.wall_texture_xoffset = (int)r->graph.raycast.hor_coll_point_x % \
					  SQUARE_SIZE;
	if (r->graph.raycast.ray_angle > 0 && r->graph.raycast.ray_angle < 180)
		r->player.compass = NORTH;
	else
		r->player.compass = SOUTH;
}

int	find_ver_coll_point(t_rain *r)
{
	if (r->graph.raycast.ray_angle > 90 && r->graph.raycast.ray_angle < 270)
	{
		r->graph.raycast.ray_x = (((int)r->player.pos_x >> 6) << 6) - 0.001f;
		r->graph.raycast.ray_y = r->player.pos_y + \
			(r->player.pos_x - r->graph.raycast.ray_x) * \
			tan(deg_to_rad(r->graph.raycast.ray_angle));
		r->graph.raycast.offset_x = -SQUARE_SIZE;
		r->graph.raycast.offset_y = -r->graph.raycast.offset_x * \
			tan(deg_to_rad(r->graph.raycast.ray_angle));
	}
	else if ((r->graph.raycast.ray_angle > 270 && \
			r->graph.raycast.ray_angle <= 360) || \
			(r->graph.raycast.ray_angle >= 0 && r->graph.raycast.ray_angle < 90))
	{
		r->graph.raycast.ray_x = (((int)r->player.pos_x >> 6) << 6) + SQUARE_SIZE;
		r->graph.raycast.ray_y = r->player.pos_y + \
			(r->player.pos_x - r->graph.raycast.ray_x) * \
			tan(deg_to_rad(r->graph.raycast.ray_angle));
		r->graph.raycast.offset_x = SQUARE_SIZE;
		r->graph.raycast.offset_y = -r->graph.raycast.offset_x * \
			tan(deg_to_rad(r->graph.raycast.ray_angle));
	}
	else
		return (0);
	return (1);
}

float	calc_ver_coll_dist(t_rain *r)
{
	int		index;
	float	distance;

	index = 0;
	while (index < (r->index.width / 2))
	{
		r->graph.raycast.map_x = ((int)r->graph.raycast.ray_x) >> 6;
		r->graph.raycast.map_y = ((int)r->graph.raycast.ray_y) >> 6;
		if (r->graph.raycast.map_x >= 0 && r->graph.raycast.map_x < (r->index.width / 2)
				&& r->graph.raycast.map_y >= 0 && r->graph.raycast.map_y < (r->index.y / 2)
			&& r->stage.grid[r->graph.raycast.map_y][r->graph.raycast.map_x] == '#')
		{
			r->graph.raycast.ver_coll_point_y = r->graph.raycast.ray_y;
			r->coor.x = r->graph.raycast.ray_x;
			r->coor.y = r->graph.raycast.ray_y;
			distance = ray_collision_distance(&r->player, r->coor);
			return (distance);
		}
		else
		{
			r->graph.raycast.ray_x += r->graph.raycast.offset_x;
			r->graph.raycast.ray_y += r->graph.raycast.offset_y;
			index++;
		}
	}
	return (100000);
}

void	save_vertical(t_rain *r, float ver_coll_dist)
{
	r->graph.raycast.closest_coll_dist = ver_coll_dist;
	r->graph.raycast.wall_texture_xoffset = (int)r->graph.raycast.ver_coll_point_y % \
					  SQUARE_SIZE;
	if (r->graph.raycast.ray_angle > 90 && r->graph.raycast.ray_angle < 270)
		r->player.compass = WEST;
	else
		r->player.compass = EAST;
}

int	raycast(t_rain *r)
{
	float	hor_coll_dist;
	float	ver_coll_dist;
	//float	fish_eye_fix;

	hor_coll_dist = 100000;
	ver_coll_dist = 100000;
	if (find_hor_coll_point(r))
		hor_coll_dist = calc_hor_coll_dist(r);
	if (find_ver_coll_point(r))
		ver_coll_dist = calc_ver_coll_dist(r);
	if (ver_coll_dist < hor_coll_dist)
		save_vertical(r, ver_coll_dist);
	else
		save_horizontal(r, hor_coll_dist);
	//fish_eye_fix = r->player.pos_angle - r->graph.raycast.ray_angle;
	//r->graph.raycast.closest_coll_dist = r->graph.raycast.closest_coll_dist * cos(deg_to_rad(fish_eye_fix));
	return (0);
}

//	Beginning of drawing the three-dimensional space.
static int	draw_space(t_rain *r)
{
	int	ray_count;

	SDL_FillRect(r->graph.surf, NULL, 0x433a59);
	r->graph.raycast.ray_angle = r->player.pos_angle + (FOV / 2);
	if (r->graph.raycast.ray_angle > 360)
		r->graph.raycast.ray_angle -= 360;
	else if (r->graph.raycast.ray_angle < 0)
		r->graph.raycast.ray_angle += 360;
	ray_count = 0;
	
	printf("\n/Draw_space() Player Angle: %f \n", r->player.pos_angle);

	while (ray_count < r->graph.width)
	{
		raycast(r);
		if (ray_count == r->graph.width / 2)
			printf("/Draw_space() Closest_coll_dist: %f", r->graph.raycast.closest_coll_dist);

		if (r->graph.raycast.closest_coll_dist > 0)
			column_render(r, ray_count);
		r->graph.raycast.ray_angle -= r->graph.raycast.degrees_per_ray;
		if (r->graph.raycast.ray_angle > 360)
			r->graph.raycast.ray_angle -= 360;
		else if (r->graph.raycast.ray_angle < 0)
			r->graph.raycast.ray_angle += 360;
		ray_count++;
	}
	return (0);
}

//	Draws the user array map in the corner of the screen.
static int	draw_arraymap(t_rain *r)
{
	int	x;
	int	y;

	if (r->editor.array[0] != NULL)
	{
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
	}
	return (0);
}

//	The graphical render order: Fill in black, draw the 3D space, draw the
//	array map in the window corner, update the window.
int	render(t_rain *r)
{
	SDL_FillRect(r->graph.surf, NULL, 0);
	if (draw_space(r) == ERROR)
		return (ERROR);
	if (draw_arraymap(r) == ERROR)
		return (ERROR);
	if (SDL_UpdateWindowSurface(r->graph.win) == ERROR)
		return (ERROR);
	return (0);
}

//	Initializes the necessary player variables before rendering.
int	initialize_player(t_rain *r)
{
	if (!(r->stage.start_x) || !(r->stage.start_y))
		return (ERROR);
	r->player.move_speed = MOVE_SPEED;

	printf("\n/STAGE(): start.x_ %d \n", r->stage.start_x);
	printf("/STAGE(): start.y_ %d \n", r->stage.start_y);

	r->player.pos_x = (double)SQUARE_SIZE * (r->stage.start_x + 1) - \
						 ((double)SQUARE_SIZE / 2.0);
	r->player.pos_y = (double)SQUARE_SIZE * (r->stage.start_y + 1) - \
						 ((double)SQUARE_SIZE / 2.0);
	
	printf("\n/Player(): Pos.x_ %f \n", r->player.pos_x);
	printf("/Player(): Pos.y_ %f \n", r->player.pos_y);

	r->player.pos_angle = 90;
	r->player.dir_x = cos(deg_to_rad(r->player.pos_angle));
	r->player.dir_y = -sin(deg_to_rad(r->player.pos_angle));
	return (0);
}

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
int	initialize_media(t_graph *g)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > SDL_ERROR)
	{
		g->scale = SCALE;
		g->width = (WIDTH * g->scale);
		g->height = (HEIGHT * g->scale);
		g->scanline = TRUE;
		g->win = SDL_CreateWindow(TITLE, 0, 0, g->width, g->height, 0);
		g->surf = SDL_GetWindowSurface(g->win);
		if (g->win != NULL || g->surf != NULL)
		{
			g->map = PLAYER_MAP;
			g->raycast.plane_distance = (double)(g->width / 2)
				/ tan(deg_to_rad(FOV / 2));

			printf("\n/Init_media(): Plane_Distance_ %f \n",
					g->raycast.plane_distance);

			g->raycast.degrees_per_column = (double)g->width / (double)FOV;
			g->raycast.degrees_per_ray = (double)FOV / (double)g->width;
			return (0);
		}
	}
	else
	{
		g->sdl_error_string = SDL_GetError();
		write(1, "SDL Error: ", 11);
		write(1, g->sdl_error_string, ft_strlen(g->sdl_error_string));
	}
	return (ERROR);
}

// Beginning of graphical function calls. Runs the graphical sequences in the
// order of: initialization, rendering, looping.
int	graphic_interface(t_rain *rain)
{
	if (initialize_media(&rain->graph) == ERROR)
		return (error(SDL_FAIL));
	if (initialize_player(rain) == ERROR)
		return (error(RENDER_FAIL));
	if (render(rain) == ERROR)
		return (error(RENDER_FAIL));
	sdl_loop(rain);
	return (0);
}
