/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/08 17:30:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	initialize(t_graph graph)
{
	//SDL_Init(SDL_INIT_VIDEO);
	graph.win = SDL_CreateWindow(TITLE, 0, 0, WIDTH, HEIGHT, 0);
	if (graph.win == NULL)
		return (ERROR);
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

int	render(t_system *system, t_editor *editor, t_index *index)
{
	t_graph	graph;

	ft_bzero(&graph, sizeof(t_graph));
	if (initialize(graph) == ERROR)
		return (error(SDL_FAIL));
	if (system && editor && index)
	{
		//
	}
	SDL_loop(graph);
	SDL_DestroyWindow(graph.win);
	SDL_Quit();
	return (0);
}
