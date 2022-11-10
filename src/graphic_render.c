/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 18:14:58 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static void	draw_minimap(t_rain *r)
{
	int	i;

	if (r->editor.array[0] != '\0')
	{
		r->graph.y = 10;
		r->graph.x = 480;
		i = 0;
		while (i <= (r->index.width * 2))
		{
			pixel_put(&r->graph);
			r->graph.y = (10 + (r->index.y * 2));
			pixel_put(&r->graph);
			r->graph.y = 10;
			r->graph.x++;
			i++;
		}
		r->graph.y = 10;
		r->graph.x = 480;
		i = 0;
		while (i <= (r->index.y * 2))
		{
			pixel_put(&r->graph);
			r->graph.x = (480 + (r->index.width * 2));
			pixel_put(&r->graph);
			r->graph.x = 480;
			r->graph.y++;
			i++;
		}
	}
}

int	render(t_rain *r)
{
	r->index.i = 0;
	int row = 0;
	r->graph.x = 5;
	r->graph.y = 5;
	r->graph.color = 0xFFFFFF;
	draw_minimap(r);
	r->graph.x = 5;
	r->graph.y = 5;
	while (row != r->index.y)
	{
		while (r->index.i != r->index.width)
		{
			pixel_put(&r->graph);
			r->graph.x += 5;
			r->index.i++;
		}
		row++;
		r->graph.x = 5;
		r->index.i = 0;
		r->graph.y += 5;
	}
	SDL_UpdateWindowSurface(r->graph.win);
	write(1, "update. \n", 9);
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
