/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/30 17:21:45 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//	A pixel drawing function for the SDL surface, created to make the rendering
//	process more simpler.
void	pixel_put(t_graph *g, int x_source, int y_source, int colour)
{
	int	x;
	int	y;
	int	w;

	x = (x_source * g->scale);
	y = (y_source * g->scale);
	w = g->width;
	((uint32_t *)g->surf->pixels)[(x++) + (y * w)] = (uint32_t)colour;
	if (g->scale == 2)
	{
		((uint32_t *)g->surf->pixels)[x + ((y++) * w)] = (uint32_t)colour;
		((uint32_t *)g->surf->pixels)[(x--) + (y * w)] = (uint32_t)colour;
		((uint32_t *)g->surf->pixels)[x + (y * w)] = (uint32_t)colour;
	}
}

//	'Vline()' (vertical line) function draws a line of three colors on the
//	graphical window.
void	vline(t_graph *g, int x_source, int y_source1, int y_source2)
{
	uint32_t	*pix;
	int			y;
	int			y1;
	int			y2;

	pix = (uint32_t *)g->surf->pixels;
	y1 = clamp(y_source1, 0, HEIGHT - 1);
	y2 = clamp(y_source2, 0, HEIGHT - 1);
	if (y2 == y1)
		pix[y1 * WIDTH + x_source] = g->top_color;
	else if (y2 > y1)
	{
		pix[y1 * WIDTH + x_source] = g->top_color;
		y = y1 + 1;
		while (y < y2)
		{
			y++;
			pix[y * WIDTH + x_source] = g->middle_color;
		}
		pix[y2 * WIDTH + x_source] = g->bottom_color;
	}
}

//	'sdl_loop()' keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls.
void	sdl_loop(t_rain *rain)
{
	while (ENDLESS)
	{
		keyboard(rain);
		if (SDL_PollEvent(&rain->graph.e) && rain->graph.e.type == SDL_QUIT)
			break ;
	}
}
