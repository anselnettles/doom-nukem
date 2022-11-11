/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/11 13:12:07 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static void	draw_slot(t_rain *r)
{
	int i;
	i = 0;
	while (i != 3)
	{
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		i++;
		r->graph.y++;
		r->graph.x -= 2;
	}
	r->graph.y -= 3;
	i = 0;
	r->graph.color = SLOT;
		r->graph.x--;
		r->graph.y--;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x += 2;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.y++;
		pixel_put(&r->graph);
		r->graph.x -= 4;
		pixel_put(&r->graph);
		r->graph.y += 2;
		pixel_put(&r->graph);
		r->graph.x += 4;
		pixel_put(&r->graph);
		r->graph.x -= 4;
		r->graph.y++;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x += 2;
		pixel_put(&r->graph);
		r->graph.x++;
		pixel_put(&r->graph);
		r->graph.x -= 3;
		r->graph.y -= 3;
}

static void	draw_minimap(t_rain *r)
{
	int	x;
	int	y;

	if (r->editor.array[0] != NULL) //how to make this check more useful?
	{
		r->graph.y = 10;
		r->graph.x = 460;			// default location for the map?
		x = 0;
		y = 0;
		while (y != r->index.y)
		{
			while (x != r->index.width)
			{
				if (r->editor.array[y][x] == '#' || r->editor.array[y][x] == '/'
						|| r->editor.array[y][x] == '\\'
						|| r->editor.array[y][x] == '*')
					r->graph.color = WALL;
				else if (r->editor.array[y][x] == '0')
					r->graph.color = PIT;
				else if (r->editor.array[y][x] >= '1' && r->editor.array[y][x] <= '9')
					r->graph.color = FLOOR;
				else if (r->editor.array[y][x] == 'a')
					r->graph.color = SKY;
				else if (r->editor.array[y][x] >= 'b' && r->editor.array[y][x] <= 'j')
					r->graph.color = CEILING;
				else
					r->graph.color = EMPTY;
				draw_slot(r);
				x++;
				r->graph.x += 6;
			}
			x = 0;
			r->graph.x = 460;
			y++;
			r->graph.y += 6;
		}
	}
}

int	render(t_rain *r)
{
	r->index.i = 0;
	r->graph.x = 5;
	r->graph.y = 5;
	r->graph.color = 0xFFFFFF;
	draw_minimap(r);
	SDL_UpdateWindowSurface(r->graph.win);
	write(1, "render", 6);
	return (0);
}

int	initialize(t_graph *g)
{
	if (SDL_Init(SDL_INIT_VIDEO) || SDL_Init(SDL_INIT_EVENTS) <= SDL_ERROR)
		return (ERROR);
	g->scale = SCALE;
	g->width = WIDTH * g->scale;
	g->height = HEIGHT * g->scale;
	g->win = SDL_CreateWindow(TITLE, 0, 0, g->width, g->height, 0);
	if (g->win == NULL)
		return (ERROR);
	g->surf = SDL_GetWindowSurface(g->win);
	if (g->surf == NULL)
		return (ERROR);
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
