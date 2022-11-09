/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/09 13:22:36 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	pixel_put(SDL_Surface *surf, int x, int y, uint32_t color)
{
	((uint32_t *)surf->pixels)[x + (y * WIDTH)] = color;
}

int	render(t_rain *r)
{
	r->graph.x = WIDTH / 2;
	r->graph.y = HEIGHT / 2;
	r->graph.color = 0xFFFFFF;
	pixel_put(r->graph.surf, r->graph.x, r->graph.y, r->graph.color);
	SDL_UpdateWindowSurface(r->graph.win);
	return (0);
}

int	initialize(t_graph *graph)
{
	if (SDL_Init(SDL_INIT_VIDEO) || SDL_Init(SDL_INIT_EVENTS) == -1)
		return (ERROR);
	graph->win = SDL_CreateWindow(TITLE, 0, 0, WIDTH, HEIGHT, 0);
	if (graph->win == NULL)
		return (ERROR);
	graph->surf = SDL_GetWindowSurface(graph->win);
	if (graph->surf == NULL)
		return (ERROR);
	return (0);
}

void	SDL_loop(t_graph *graph)
{
	while (ENDLESS)
	{
		if (SDL_PollEvent(&graph->e) && graph->e.type == SDL_QUIT)
			break ;
	}
}

int	graphic_interface(t_rain *rain)
{
	if (initialize(&rain->graph) == ERROR)
		return (error(SDL_FAIL));
	if (render(rain) == ERROR)
		return (error(RENDER_FAIL));
	SDL_loop(&rain->graph);
	//SDL_DestroyWindow(graph.win);
	//SDL_Quit();
	return (0);
}
