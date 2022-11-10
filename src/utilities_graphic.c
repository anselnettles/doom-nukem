/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 17:30:14 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//A pixel drawing function for the SDL surface, created to make the rendering
//process more simpler.
void	pixel_put(t_graph *g)
{
	int	x;
	int	y;
	int	width;

	x = g->x * g->scaler;
	y = g->y * g->scaler;
	width = g->width;
	((uint32_t *)g->surf->pixels)[x + (y * (width))] = g->color;
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