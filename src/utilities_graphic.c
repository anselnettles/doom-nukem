/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/06 13:21:44 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//	A pixel drawing function for the SDL surface, created to make the rendering
//	process more simpler.
void	pixel_put(t_graph *g, int x_src, int y_src, uint32_t color)
{
	uint32_t	*pix;
	int			x;
	int			y;
	int			wth;

	pix = g->surf->pixels;
	x = (x_src * g->scale);
	y = (y_src * g->scale);
	wth = g->width;
	pix[(x) + (y * wth)] = color << (g->scanline * (y_src % 2));
	if (g->scale >= 2)
	{
		pix[(x + 1) + ((y) * wth)] = color << (g->scanline * (y_src % 2));
		pix[(x) + ((y + 1) * wth)] = color;
		pix[(x + 1) + ((y + 1) * wth)] = color;
		if (g->scale == 3)
		{
			pix[(x + 2) + ((y) * wth)] = color << (g->scanline * (y_src % 2));
			pix[(x + 2) + ((y + 1) * wth)] = color;
			pix[(x) + ((y + 2) * wth)] = color << (g->scanline * (y_src % 2));
			pix[(x + 1) + ((y + 2) * wth)] = color << (g->scanline * (y_src % 2));
			pix[(x + 2) + ((y + 2) * wth)] = color << (g->scanline * (y_src % 2));
		}
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
			if (g->scanline == TRUE && (y % 2 != 0))
				pix[(y * width) + x_source] = (g->middle_color << 1);
			else
				pix[(y * width) + x_source] = g->middle_color;
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
