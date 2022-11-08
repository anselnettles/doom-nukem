/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/08 20:04:37 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	pixel_put(SDL_Surface *surf, int x, int y, uint32_t color)
{
//	printf("pixel: %d \n", ((uint32_t *)surf->pixels[x + (y * WIDTH)]));
	((uint32_t *)surf->pixels)[x + (y * WIDTH)] = color;
}

int	render(t_graph graph, t_editor *editor, t_index *index)
{
	graph.x = WIDTH / 2;
	graph.y = HEIGHT / 2;
	graph.color = 0xFFFFFF;
	pixel_put(graph.surf, graph.x, graph.y, graph.color);
	SDL_UpdateWindowSurface(graph.win);
	if (editor)
		;
	if (index)
		;
	return (0);
}

int	initialize(t_graph graph)
{
	//SDL_Init(SDL_INIT_VIDEO);
	graph.win = SDL_CreateWindow(TITLE, 0, 0, WIDTH, HEIGHT, 0);
	if (graph.win == NULL)
		return (ERROR);
	graph.surf = SDL_GetWindowSurface(graph.win);
	if (graph.surf == NULL)
		return (ERROR);
	graph.surf->pixels = ft_memalloc(sizeof(WIDTH * HEIGHT));
	return (0);
}

void	SDL_loop(t_graph graph)
{
	while (ENDLESS)
	{
		if (SDL_PollEvent(&graph.e) && graph.e.type == SDL_QUIT)
			break ;
	}
}

int	graphic_interface(t_graph graph, t_system *system, t_editor *editor, t_index *index)
{
	//t_graph	graph;

	if (initialize(graph) == ERROR)
		return (error(SDL_FAIL));
	if (render(graph, editor, index) == ERROR)
		return (error(RENDER_FAIL));
	if (system && editor && index)
	{
		//
	}
	SDL_loop(graph);
	//SDL_DestroyWindow(graph.win);
	//SDL_Quit();
	return (0);
}
