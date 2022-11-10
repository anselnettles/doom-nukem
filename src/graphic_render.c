/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 17:26:42 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static void	draw_minimap(t_rain *r)
{
	if (r->editor.array[0] != '\0')
	{
		r->graph.y = 5;
		r->graph.x = 600 * r->graph.scaler;
		while (r->graph.x < (r->graph.width - 5))
		{
			pixel_put(&r->graph);
			r->graph.y = ((r->index.y * r->graph.scaler) * 2);
			pixel_put(&r->graph);
			r->graph.y = 5;
			r->graph.x++;
		}
		r->graph.x = 600 * r->graph.scaler;
		while (r->graph.y < (((r->index.y * r->graph.scaler) * 2) + 5))
		{
			pixel_put(&r->graph);
			r->graph.x += ((r->index.width * r->graph.scaler) * 1.30);
			pixel_put(&r->graph);
			r->graph.x = 600 * r->graph.scaler;
			r->graph.y++;
		}
	}
	//draw slots;
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
	g->scaler = SCALE;
	g->width = WIDTH * g->scaler;
	g->height = HEIGHT * g->scaler;
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
