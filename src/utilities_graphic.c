/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/09 16:46:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//A pixel drawing function for the SDL surface, created to make the rendering
//process more simpler.
void	pixel_put(SDL_Surface *surf, int x, int y, uint32_t color)
{
	((uint32_t *)surf->pixels)[x + (y * WIDTH)] = color;
}

//'sdl_loop()' keeps Simple Direct MediaLayer's PollEvent consistently running.
void	sdl_loop(t_graph *graph)
{
	while (ENDLESS)
	{
		keyboard(graph);
		if (SDL_PollEvent(&graph->e) && graph->e.type == SDL_QUIT)
			break ;
	}
}
