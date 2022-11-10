/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 12:32:22 by aviholai         ###   ########.fr       */
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
	printf("rows: %d. \n", r->index.y);
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
	return (0);
}

int	initialize(t_graph *g)
{
	if (SDL_Init(SDL_INIT_VIDEO) || SDL_Init(SDL_INIT_EVENTS) <= SDL_ERROR)
		return (ERROR);
	g->scaler = 2;
	g->win = SDL_CreateWindow(TITLE, 0, 0, WIDTH * g->scaler, HEIGHT * g->scaler, 0);
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
	sdl_loop(&rain->graph);
	return (0);
}
