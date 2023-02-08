/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/08 14:24:49 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	A pixel drawing function for the SDL surface, created to make the rendering
//	process more simpler.
//	Applies a multiplication of the needed pixels as by the scaling toggle,
//	one pixel for 1X scale and four pixels for 2X scale.
//	The scanline visual effect ('gfx->scanline') is applied alternatively to
//	color of the column to create an aesthetic alternating scanline effect,
//	when toggled on.
int	pixel_put(t_gfx *gfx, int x_src, int y_src, uint32_t color)
{
	uint32_t	*pix;
	int			x;
	int			y;
	int			wth;


	if (x_src > gfx->width - 1 || y_src > gfx->height - 1)
		return (ERROR);
	pix = gfx->screen->pixels;
	x = (x_src * gfx->scale);
	y = (y_src * gfx->scale);
	wth = gfx->width;
	pix[(x) + (y * wth)] = color << (gfx->scanline * (y_src % 2));
	if (gfx->scale >= 2)
	{
		pix[(x + 1) + ((y) * wth)] = color << (gfx->scanline * (y_src % 2));
		pix[(x) + ((y + 1) * wth)] = color;
		pix[(x + 1) + ((y + 1) * wth)] = color;
	}
	return (0);
}

/*
//'Texture_color()' picks the correct RGB color from the correct texture
//file's pixels, corresponding to the parameter texture_y location.
static uint32_t	txtr(t_drown *d, float texture_y)
{
	SDL_Surface	*texture;
	uint32_t	color;
	int			scale_y;
	int			scale_x;

	texture = NULL;
	scale_y = (int)(156 * texture_y) / SQUARE_SIZE;
	scale_x = (256 * d->graph.cast.texture_xoffset) / SQUARE_SIZE;
	if (d->player.compass == NORTH)
		texture = d->graph.texture[0];
	else if (d->player.compass == EAST)
		texture = d->graph.texture[1];
	else if (d->player.compass == SOUTH)
		texture = d->graph.texture[2];
	else if (d->player.compass == WEST)
		texture = d->graph.texture[3];
	color = ((uint32_t *)texture->pixels)[scale_x + (scale_y * texture->w)];
	return (color);
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
void	vline(t_drown *d, t_location lo, float y, uint32_t color)
{
	uint32_t	*pix;

	pix = d->graph.surf->pixels;
	lo.y1 = clamp((int)lo.start_y, 0, d->graph.height - 1);
	lo.y2 = clamp((int)lo.end_y, 0, d->graph.height - 1);
	if (lo.y2 == lo.y1)
		pix[(lo.y1 * d->graph.width) + (int)lo.start_x] = BLUE_OUTLINE;
	else if (lo.y2 > lo.y1)
	{
		pix[(lo.y1 * d->graph.width) + (int)lo.start_x] = BLUE_OUTLINE;
		lo.y = lo.y1 + 1;
		while (lo.y < lo.y2)
		{
			if (color == 0)
				pix[((lo.y++) * d->graph.width) + (int)lo.start_x] = txtr(d, y);
			else
			{
				pix[((lo.y++) * d->graph.width) + (int)lo.start_x] = color++;
				if (d->graph.scale >= 2)
					pix[((lo.y++) * d->graph.width) + (int)lo.start_x] = color;
			}
			y += (float)d->graph.cast.texture_yincrement;
		}
		pix[(lo.y2 * d->graph.width) + (int)lo.start_x] = BROWN_OUTLINE;
	}
}*/
