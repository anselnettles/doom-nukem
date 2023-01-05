/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/05 14:18:11 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//	A pixel drawing function for the SDL surface, created to make the rendering
//	process more simpler.
void	pixel_put(t_graph *g, int x_source, int y_source, int colour)
{
	uint32_t	*pix;
	int	x;
	int	y;
	int	width;

	pix = (uint32_t *)g->surf->pixels;
	x = (x_source * g->scale);
	y = (y_source * g->scale);
	width = g->width;
	pix[(x++) + (y * width)] = (uint32_t)colour;
	if (g->scale == 2)
	{
		pix[x + ((y++) * width)] = (uint32_t)colour;
		pix[(x--) + (y * width)] = (uint32_t)colour;
		pix[x + (y * width)] = (uint32_t)colour;
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
	int			width;

	pix = (uint32_t *)g->surf->pixels;
	y1 = clamp(y_source1, 0, g->height - 1);
	y2 = clamp(y_source2, 0, g->height - 1);
	width = g->width;
	if (y2 == y1)
		pix[(y1 * width) + x_source] = g->top_color;
	else if (y2 > y1)
	{
		pix[(y1 * width) + x_source] = g->top_color;
		y = y1 + 1;
		while (y < y2)
		{
			if (y % 2 != 0)
				pix[(y * width) + x_source] = g->middle_color;
			else
			{
				if (g->scanline == TRUE)
					pix[(y * width) + x_source] = (g->middle_color << 1);
				else
					pix[(y * width) + x_source] = g->middle_color;
			}
			y++;
		}
		pix[(y2 * width) + x_source] = g->bottom_color;
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
