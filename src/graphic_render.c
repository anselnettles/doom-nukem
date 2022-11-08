/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:53:39 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/08 16:56:25 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	initialize(t_graph graph)
{
	SDL_Init(SDL_INIT_VIDEO);
	graph.win = SDL_CreateWindow(TITLE, 0, 0, WIDTH, HEIGHT, 0);
}

int	render(t_system *system, t_editor *editor, t_index *index)
{
	t_graph	graph;

	ft_bzero(&graph, sizeof(t_graph));
	initialize(graph);
	while (1)
	{
		if (SDL_PollEvent(&graph.e) && graph.e.type == SDL_QUIT)
			break ;
	}
	SDL_DestroyRenderer(graph.ren);
	SDL_DestroyWindow(graph.win);
	SDL_Quit();
	if (system && editor && index)
	{
		//
	}
	return (0);
}
