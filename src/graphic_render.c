/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/11 18:23:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static int	draw_slot_outline(t_rain *r)
{
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x + 2, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y - 1, SLOT);
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y, SLOT);
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y + 2, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y + 2, SLOT);
	pixel_put(&r->graph, r->graph.x - 1, r->graph.y + 3, SLOT);
	pixel_put(&r->graph, r->graph.x, r->graph.y + 3, SLOT);
	pixel_put(&r->graph, r->graph.x + 2, r->graph.y + 3, SLOT);
	pixel_put(&r->graph, r->graph.x + 3, r->graph.y + 3, SLOT);
	return (0);
}

static int	draw_map_tile(t_rain *r, int color)
{
	pixel_put(&r->graph, r->graph.x, r->graph.y, color);
	pixel_put(&r->graph, r->graph.x + 1, r->graph.y, color);
	pixel_put(&r->graph, r->graph.x, r->graph.y + 1, color);
	pixel_put(&r->graph, r->graph.x + 1, r->graph.y + 1, color);
	return (0);
}

static int	draw_pl_tile(t_rain *r, char a[MAX + 1][MAX + 1], int x, int y)
{
	if (a[y][x] == '#' || a[y + 1][x] == '#' || a[y][x + 1] == '#'
			|| a[y +1][x + 1] == '#' || a[y][x] == '/'
			|| a[y + 1][x] == '/' || a[y][x + 1] == '/'
			|| a[y + 1][x + 1] == '/' || a[y][x] == '\\'
			|| a[y + 1][x] == '\\' || a[y][x + 1] == '\\'
			|| a[y + 1][x + 1] == '\\' || a[y][x] == '*'
			|| a[y + 1][x] == '*' || a[y][x + 1] == '*'
			|| a[y + 1][x + 1] == '*')
		draw_map_tile(r, WALL);
	else
		draw_map_tile(r, EMPTY);
	return (0);
}

static int	draw_dev_tile(t_rain *r, char a[MAX + 1][MAX + 1], int x, int y)
{
	if (a[y][x] == '#' || a[y][x] == '/' || a[y][x] == '\\'
			|| a[y][x] == '*')
		draw_map_tile(r, WALL);
	else if (a[y][x] == '0')
		draw_map_tile(r, PIT);
	else if (a[y][x] >= '1' && a[y][x] <= '9')
		draw_map_tile(r, FLOOR);
	else if (a[y][x] == 'a')
		draw_map_tile(r, SKY);	
	else if (a[y][x] >= 'b' && a[y][x] <= 'j')
		draw_map_tile(r, CEILING);
	else
		draw_map_tile(r, EMPTY);
	return (0);
}

static int	draw_arraymap(t_rain *r)
{
	int	x;
	int	y;

	if (r->editor.array[0] != NULL) //how to make this check more useful?
	{
		r->graph.y = 10;
		r->graph.x = 460;			// default location for the map?
		x = 0;
		y = 0;
		while (y <= r->index.y)
		{
			while (x <= r->index.width)
			{
				if (r->graph.map == PLAYER_MAP)
					draw_pl_tile(r, (char **)r->editor.array, x, y);
				else if (r->graph.map == DEV_MAP)
					draw_dev_tile(r, (char **)r->editor.array, x, y);
				draw_slot_outline(r);
				x++;
				if (r->graph.map == PLAYER_MAP)
					x++;
				r->graph.x += 6;
			}
			x = 0;
			r->graph.x = 460;
			y++;
			if (r->graph.map == PLAYER_MAP)
				y++;
			r->graph.y += 6;
		}
	}
	return (0);
}

int	render(t_rain *r)
{
	SDL_FillRect(r->graph.surf, NULL, 0);
	if (draw_arraymap(r) == ERROR)
		return (ERROR);
	//draw_space(r);
	SDL_UpdateWindowSurface(r->graph.win);
	write(1, "[Ren'd]", 7);
	return (0);
}

int	initialize(t_graph *g)
{
	if (SDL_Init(SDL_INIT_VIDEO || SDL_INIT_EVENTS) <= SDL_ERROR)
	{
		g->SDL_error_string = SDL_GetError();
		write(1, g->SDL_error_string, ft_strlen(g->SDL_error_string));
		return (ERROR);
	}
	g->scale = SCALE;
	g->width = WIDTH * g->scale;
	g->height = HEIGHT * g->scale;
	g->win = SDL_CreateWindow(TITLE, 0, 0, g->width, g->height, 0);
	g->surf = SDL_GetWindowSurface(g->win);
	if (g->win == NULL || g->surf == NULL)
	{
		g->SDL_error_string = SDL_GetError();
		write(1, g->SDL_error_string, ft_strlen(g->SDL_error_string));
		return (ERROR);
	}
	g->map = PLAYER_MAP;
	return (0);
}

int	graphic_interface(t_rain *rain)
{
	if (initialize(&rain->graph) == ERROR)
		return (error(SDL_FAIL));
	if (render(rain) == ERROR)
		return (error(RENDER_FAIL));
	sdl_loop(rain);
	return (0);
}
