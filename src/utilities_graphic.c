/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/11 15:08:32 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//WIP.
static uint32_t	texture_color(t_rain *r, int value)
{
	SDL_Surface	*texture;
	//uint32_t	*color;
	int			scale_y;
	int			scale_x;

	texture = NULL;
	scale_y = 256 * value / 64;
	scale_x = 256 * r->graph.raycast.wall_texture_xoffset / 64;
	if (value >= 0x000001)
		return (value);
	if (r->player.compass == NORTH)
		texture = r->texture.file[0];
	else if (r->player.compass == EAST)
		texture = r->texture.file[1];
	else if (r->player.compass == SOUTH)
	{
		texture = r->texture.file[2];
		scale_x = 128 * r->graph.raycast.wall_texture_xoffset / 64;
	}
	else if (r->player.compass == WEST)
		texture = r->texture.file[3];
	//color = ((uint32_t *)texture->pixels)[scale_x + (scale_y * 256)];
	//											printf("%d ", color);
	//r->graph->surf->pixels[100 + (100 * r->graph.width)] = r->texture->file[0]->pixels[1 * (1 * 256)];
	return (0x8f0f0f);
}

//	A pixel drawing function for the SDL surface, created to make the rendering
//	process more simpler.
//	Applies a multiplication of the needed pixels as by the scaling toggle,
//	one pixel for 1X scale, four pixels for 2X scale and nine pixels for 3X.
//	The scanline visual effect ('g->scanline') is applied on every second pixel
//	color of the column to create an aesthetic alternating scanline effect.
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
			pix[(x +1) + ((y +2) * wth)] = color << (g->scanline * (y_src % 2));
			pix[(x +2) + ((y +2) * wth)] = color << (g->scanline * (y_src % 2));
		}
	}
}

//	'Vline()' (vertical line) function draws a line of three colors on the
//	graphical window. The start and end points are of different color only
//	to make the polygonal shapes easier to view.
//	The main color (the  middle color) is handled through the proxy function
//	'txtrclr()' (texture color) to choose a pixel color from the texture
//	image files.
//	The integer 'value' stands for the texture's saved y position which is
//	incremented each time a pixel for the main color is planted, or
//	alternatively for a HEX color value. The bit shifted color values ('<<')
//	simply adjust a little bit for a differing effect for the start and end
//	point of each column line.
//	The scanline visual effect ('r->graph.sl') is applied on every second
//	main color pixel to create an aesthetic alternating scanline effect. 
void	vline(t_rain *r, t_corf start, t_corf end, int value)
{
	uint32_t	*pix;
	int			y;
	int			y1;
	int			y2;
	int			wth;

	pix = r->graph.surf->pixels;
	y1 = clamp((int)start.y, 0, r->graph.height - 1);
	y2 = clamp((int)end.y, 0, r->graph.height - 1);
	wth = r->graph.width;
	if (y2 == y1)
		pix[(y1 * wth) + (int)start.x] = value << 3;
	else if (y2 > y1)
	{
		pix[(y1 * wth) + (int)start.x] = value << 3;
		y = y1 + 1;
		while (y < y2)
		{
			pix[(y * wth) + (int)start.x] = texture_color(r, value)
				<< (r->graph.scanline * (y % 2));
			value += r->graph.raycast.wall_texture_yincrement;
			y++;
		}
		pix[(y2 * wth) + (int)start.x] = value << 5;
	}
}
