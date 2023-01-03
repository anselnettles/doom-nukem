/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:05:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/12/28 10:34:31 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

/*
static void	draw_wall(t_rain *r, int centre_x, int centre_y)
{
	int		i;
	int		s;
	int		len;
	int		value;

	i = 0;
	s = r->graph.scale;
	len = ((32 + (int)r->player.where.z) * s);
	value = 0;
	r->graph.top_color = (WALL_TEXTURE + 00076000);
	r->graph.middle_color = WALL_TEXTURE;
	r->graph.bottom_color = (WALL_TEXTURE + 00076000);
	while (i < (32 + r->player.where.z) * (float)r->graph.scale)
	{
		vline(&r->graph, centre_x - i, centre_y - len - (value), centre_y + len + (value));
		vline(&r->graph, centre_x + i, centre_y - len + (value), centre_y + len - (value));
		if (i == (len - 2))
			r->graph.middle_color = (WALL_TEXTURE + 00076000);
		i++;
		value += (int)r->player.angle;
	}
}
*/

/*
static int	check_square(t_rain *r, char a[MAX + 1][MAX + 1], int x, int y)
{
	if (a[y][x] == '#' || a[y + 1][x] == '#' || a[y][x + 1] == '#'
			|| a[y + 1][x + 1] == '#' || a[y][x] == '/'
			|| a[y + 1][x] == '/' || a[y][x + 1] == '/'
			|| a[y + 1][x + 1] == '/' || a[y][x] == '\\'
			|| a[y + 1][x] == '\\' || a[y][x + 1] == '\\'
			|| a[y + 1][x + 1] == '\\' || a[y][x] == '*'
			|| a[y + 1][x] == '*' || a[y][x + 1] == '*'
			|| a[y + 1][x + 1] == '*' || a[y][x] == '['
			|| a[y + 1][x] == '[' || a[y][x + 1] == '['
			|| a[y + 1][x + 1] == '[' || a[y][x] == ']'
			|| a[y + 1][x] == ']' || a[y][x + 1] == ']'
			|| a[y + 1][x + 1] == ']')
		return (0);
	else
	{
		//make wall smaller;
		check_square(r, a, x, y - 2);
	}
	return (0);
}*/

static void	draw_loops(t_rain *r, t_pointf start, t_pointf end)
{
	if (r->raycast.projected_slice_height < r->graph.height)
	{
		end.y = (r->graph.height / 2) - (r->raycast.projected_slice_height / 2);
		while (start.y < end.y)
			start.y++;
		end.y += r->raycast.projected_slice_height;
	}
	while (start.y < end.y)
	{
		vline(&r->graph, start.x, start.y, end.y);
		//txtr_y += mlx->raycast.wall_texture_yincrement;
		start.y++;
	}
	if (end.y < r->graph.height)
	{
		while (start.y < r->graph.height)
			start.y++;
	}
}

void	draw_column(t_rain *r, int ray_nbr)
{
	t_raycast	*raycast;
	t_pointf	start;
	t_pointf	end;
	//float		texture_y;

	raycast = &r->raycast;
	raycast->projected_slice_height = (float)SQUARE_SIZE / \
			raycast->closest_coll_dist * raycast->dist_to_proj_plane;
	raycast->wall_texture_yincrement = (float)SQUARE_SIZE / \
			(float)raycast->projected_slice_height;
	raycast->wall_texture_yoffset = 0;
	if (raycast->projected_slice_height > r->graph.height)
	{
		raycast->wall_texture_yoffset = \
			(raycast->projected_slice_height - r->graph.height) / 2;
		raycast->projected_slice_height = r->graph.height;
	}
	//texture_y = raycast->wall_texture_yoffset * raycast->wall_texture_yincrement;
	start.x = ray_nbr;
	start.y = 0;
	end.x = ray_nbr;
	end.y = r->graph.height;
	draw_loops(r, start, end);
	//vline(&r->graph, start.x, start.y, end.y);
}


float	ray_collision_distance(t_player *player, t_pointf collision)
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
	if (r->raycast.ray_angle > 0 && r->raycast.ray_angle < 180)
	{
		r->raycast.ray_y = (((int)r->player.pos_y >> 6) << 6) - 0.001f;
		r->raycast.ray_x = r->player.pos_x + \
			(r->player.pos_y - r->raycast.ray_y) / \
			tan(deg_to_rad(r->raycast.ray_angle));
		r->raycast.offset_y = -SQUARE_SIZE;
		r->raycast.offset_x = -r->raycast.offset_y / \
			tan(deg_to_rad(r->raycast.ray_angle));
	}
	else if (r->raycast.ray_angle > 180 && \
				r->raycast.ray_angle < 360)
	{
		r->raycast.ray_y = (((int)r->player.pos_y >> 6) << 6) + SQUARE_SIZE;
		r->raycast.ray_x = r->player.pos_x + \
			(r->player.pos_y - r->raycast.ray_y) / \
			tan(deg_to_rad(r->raycast.ray_angle));
		r->raycast.offset_y = SQUARE_SIZE;
		r->raycast.offset_x = -r->raycast.offset_y / \
			tan(deg_to_rad(r->raycast.ray_angle));
	}
	else
		return (0);
	return (1);
}

float	calc_hor_coll_dist(t_rain *r)
{
	int	index;

	index = 0;
	while (index < (r->index.y / 2))
	{
		r->raycast.map_x = ((int)r->raycast.ray_x) >> 6;
		r->raycast.map_y = ((int)r->raycast.ray_y) >> 6;
		if (r->raycast.map_x >= 0 && r->raycast.map_x < (r->index.x) && \
			r->raycast.map_y >= 0 && r->raycast.map_y < (r->index.y / 2) && \
			r->stage.grid[r->raycast.map_y][r->raycast.map_x] != 0)
		{
			r->raycast.hor_coll_point_x = r->raycast.ray_x;
			return (ray_collision_distance(&r->player, \
				(t_pointf){r->raycast.ray_x, r->raycast.ray_y}));
		}
		else
		{
			r->raycast.ray_x += r->raycast.offset_x;
			r->raycast.ray_y += r->raycast.offset_y;
			index++;
		}
	}
	return (100000);
}

void	save_horizontal(t_rain *r, float hor_coll_dist)
{
	r->raycast.closest_coll_dist = hor_coll_dist;
	r->raycast.wall_texture_xoffset = (int)r->raycast.hor_coll_point_x % \
					  SQUARE_SIZE;
	if (r->raycast.ray_angle > 0 && r->raycast.ray_angle < 180)
		r->player.compass = NORTH;
	else
		r->player.compass = SOUTH;
}

int	find_ver_coll_point(t_rain *r)
{
	if (r->raycast.ray_angle > 90 && r->raycast.ray_angle < 270)
	{
		r->raycast.ray_x = (((int)r->player.pos_x >> 6) << 6) - 0.001f;
		r->raycast.ray_y = r->player.pos_y + \
			(r->player.pos_x - r->raycast.ray_x) * \
			tan(deg_to_rad(r->raycast.ray_angle));
		r->raycast.offset_x = -SQUARE_SIZE;
		r->raycast.offset_y = -r->raycast.offset_x * \
			tan(deg_to_rad(r->raycast.ray_angle));
	}
	else if ((r->raycast.ray_angle > 270 && \
			r->raycast.ray_angle <= 360) || \
			(r->raycast.ray_angle >= 0 && r->raycast.ray_angle < 90))
	{
		r->raycast.ray_x = (((int)r->player.pos_x >> 6) << 6) + SQUARE_SIZE;
		r->raycast.ray_y = r->player.pos_y + \
			(r->player.pos_x - r->raycast.ray_x) * \
			tan(deg_to_rad(r->raycast.ray_angle));
		r->raycast.offset_x = SQUARE_SIZE;
		r->raycast.offset_y = -r->raycast.offset_x * \
			tan(deg_to_rad(r->raycast.ray_angle));
	}
	else
		return (0);
	return (1);
}

float	calc_ver_coll_dist(t_rain *r)
{
	int	index;

	index = 0;
	while (index < (r->index.width / 2))
	{
		r->raycast.map_y = ((int)r->raycast.ray_y) >> 6;
		if (r->raycast.map_x >= 0 && r->raycast.map_x < (r->index.width / 2) && \
			r->raycast.map_y >= 0 && r->raycast.map_y < (r->index.y / 2) && \
			r->stage.grid[r->raycast.map_y][r->raycast.map_x] != 0)
		{
			r->raycast.ver_coll_point_y = r->raycast.ray_y;
			return (ray_collision_distance(&r->player, \
				(t_pointf){r->raycast.ray_x, r->raycast.ray_y}));
		}
		else
		{
			r->raycast.ray_x += r->raycast.offset_x;
			r->raycast.ray_y += r->raycast.offset_y;
			index++;
		}
	}
	return (100000);
}

void	save_vertical(t_rain *r, float ver_coll_dist)
{
	r->raycast.closest_coll_dist = ver_coll_dist;
	r->raycast.wall_texture_xoffset = (int)r->raycast.ver_coll_point_y % \
					  SQUARE_SIZE;
	if (r->raycast.ray_angle > 90 && r->raycast.ray_angle < 270)
		r->player.compass = WEST;
	else
		r->player.compass = EAST;
}

static void	paint_sky_and_earth(t_rain *r)
{
	int	i;

	i = 0;
	while (i != (r->graph.width))
	{
		r->graph.top_color = CEILING_TEXTURE;
		r->graph.middle_color = CEILING_TEXTURE;
		r->graph.bottom_color = CEILING_TEXTURE;
		vline(&r->graph, i, 0, r->graph.height / 2);
		r->graph.top_color = FLOOR_TEXTURE;
		r->graph.middle_color = FLOOR_TEXTURE;
		r->graph.bottom_color = FLOOR_TEXTURE;
		vline(&r->graph, i, ((r->graph.height) / 2), r->graph.height);
		i++;
	}
}

int	cast(t_rain *r)
{
	float	hor_coll_dist;
	float	ver_coll_dist;
	float	fish_eye_fix;

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
	fish_eye_fix = r->player.pos_angle - r->raycast.ray_angle;
	r->raycast.closest_coll_dist = r->raycast.closest_coll_dist * \
	
	       
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
				       cos(deg_to_rad(fish_eye_fix));
	return (0);
}

//	Beginning of drawing the three-dimensional space.
static int	draw_space(t_rain *r)
{
	int	ray_nbr;

	SDL_FillRect(r->graph.surf, NULL, 0x433a59);
	paint_sky_and_earth(r);
	r->raycast.ray_angle = r->player.pos_angle + (FOV / 2);
	if (r->raycast.ray_angle > 360)
		r->raycast.ray_angle -= 360;
	else if (r->raycast.ray_angle < 0)
		r->raycast.ray_angle += 360;
	ray_nbr = 0;
	while (ray_nbr < r->graph.width)
	{
		cast(r);
		if (r->raycast.closest_coll_dist > 0)
			break;
		//	draw_column(r, ray_nbr);
		r->raycast.ray_angle -= r->raycast.degrees_per_ray;
		if (r->raycast.ray_angle > 360)
			r->raycast.ray_angle -= 360;
		else if (r->raycast.ray_angle < 0)
			r->raycast.ray_angle += 360;
		ray_nbr++;
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
	if (SDL_UpdateWindowSurface(r->graph.win) == 0)
		write(1, "[Ren'd]", 7);
	return (0);
}

//	Initializes the necessary player variables before rendering.
int	initialize_player(t_rain *r)
{
	if (!(r->stage.start_x) || !(r->stage.start_y))
		return (ERROR);
	r->player.move_speed = MOVE_SPEED;
	r->player.pos_x = (double)SQUARE_SIZE * (r->stage.start_x + 1) - \
						 ((double)SQUARE_SIZE / 2.0);
	r->player.pos_y = (double)SQUARE_SIZE * (r->stage.start_y + 1) - \
						 ((double)SQUARE_SIZE / 2.0);
	r->player.pos_angle = 180;
	r->player.dir_x = cos(deg_to_rad(r->player.pos_angle));
	r->player.dir_y = -sin(deg_to_rad(r->player.pos_angle));
	return (0);
}

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
int	initialize_media(t_graph *g)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) <= SDL_ERROR)
		{
		g->sdl_error_string = SDL_GetError();
		write(1, g->sdl_error_string, ft_strlen(g->sdl_error_string));
		return (ERROR);
	}
	g->scale = SCALE;
	g->width = (WIDTH * g->scale);
	g->height = (HEIGHT * g->scale);
	g->win = SDL_CreateWindow(TITLE, 0, 0, g->width, g->height, 0);
	g->surf = SDL_GetWindowSurface(g->win);
	if (g->win == NULL || g->surf == NULL)
	{
		g->sdl_error_string = SDL_GetError();
		write(1, "SDL Error: ", 11);
		write(1, g->sdl_error_string, ft_strlen(g->sdl_error_string));
		return (ERROR);
	}
	g->map = PLAYER_MAP;
	g->raycast.dist_to_proj_plane = (double)(g->width / 2) / \
					tan(deg_to_rad(FOV / 2));
	g->raycast.degrees_per_column = (double)g->width / (double)FOV;
	g->raycast.degrees_per_ray = (double)FOV / (double)g->width;
	return (0);
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
