/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/21 09:47:37 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//A pixel drawing function for the SDL surface, created to make the rendering
//process more simpler.
void	pixel_put(t_graph *g, int x_source, int y_source, int c)
{
	int	x;
	int	y;
	int	w;

	x = (x_source * g->scale);
	y = (y_source * g->scale);
	w = g->width;
	((uint32_t *)g->surf->pixels)[(x++) + (y * w)] = (uint32_t)c;
	if (g->scale == 2)
	{
		((uint32_t *)g->surf->pixels)[x + ((y++) * w)] = (uint32_t)c;
		((uint32_t *)g->surf->pixels)[(x--) + (y * w)] = (uint32_t)c;
		((uint32_t *)g->surf->pixels)[x + (y * w)] = (uint32_t)c;
	}
}

//'sdl_loop()' keeps Simple Direct MediaLayer's PollEvent consistently running.
void	sdl_loop(t_rain *rain)
{
	while (ENDLESS)
	{
		keyboard(rain);
		if (SDL_PollEvent(&rain->graph.e) && rain->graph.e.type == SDL_QUIT)
			break ;
	}
}
