/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/09 17:51:22 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdio.h>

int	render(t_rain *r)
{
	r->index.i = 0;
	int row = 0;
	r->graph.x = 5;
	r->graph.y = 5;
	r->graph.color = 0xFFFFFF;
	pixel_put(r->graph.surf, r->graph.y, r->graph.x, r->graph.color);
	printf("rows: %d. \n", r->index.y);
	while (row != r->index.y)
	{
		while (r->index.i != r->index.width)
		{
			pixel_put(r->graph.surf, r->graph.y, r->graph.x, r->graph.color);
			r->graph.x += 5;
			r->index.i++;
		}
		row++;
		r->graph.x = 5;
		r->index.i = 0;
		r->graph.y += 5;
	}

	SDL_UpdateWindowSurface(r->graph.win);
	return (0);
}

int	initialize(t_graph *graph)
{
	if (SDL_Init(SDL_INIT_VIDEO) || SDL_Init(SDL_INIT_EVENTS) <= SDL_ERROR)
		return (ERROR);
	graph->win = SDL_CreateWindow(TITLE, 0, 0, WIDTH, HEIGHT, 0);
	if (graph->win == NULL)
		return (ERROR);
	graph->surf = SDL_GetWindowSurface(graph->win);
	if (graph->surf == NULL)
		return (ERROR);
	return (0);
}

int	graphic_interface(t_rain *rain)
{
	if (initialize(&rain->graph) == ERROR)
		return (error(SDL_FAIL));
	if (render(rain) == ERROR)
		return (error(RENDER_FAIL));
	sdl_loop(&rain->graph);
	return (0);
}
