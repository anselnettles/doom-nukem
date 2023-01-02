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


//	Beginning of drawing the three-dimensional space.
static int	draw_space(t_rain *r)
{
	int	i;

	i = 0;
	SDL_FillRect(r->graph.surf, NULL, 0x433a59);
	if(r->editor.start_x == 0 || r->editor.start_y == 0)
		return (ERROR);
	else
	{
		//write(1, "Start X pos: ", 13);
		//write(1, &r->editor.start_x, sizeof(r->editor.start_y));
		//write(1, " Start Y pos: ", 14);
		//write(1, &r->editor.start_y, sizeof(r->editor.start_y));
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
		//draw_wall(r, (r->graph.width / 2) + (int)r->player.where.x, (r->graph.height / 2));
		//if (r->editor.array[r->editor.start_y][r->editor.start_x]
		//static unsigned	numsectors;
		//numsectors = 0;
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
	r->player.move_speed = MOVE_SPEED;
	r->player.pos_x = (double)SQUARE_SIZE * (r->editor.start_x + 1) - \
						 ((double)SQUARE_SIZE / 2.0);
	r->player.pos_y = (double)SQUARE_SIZE * (r->editor.start_y + 1) - \
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
