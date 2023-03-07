/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_filters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:40:31 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/01 23:37:04 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	draw_color_filter(t_gfx *gfx, uint32_t *pix, uint32_t color)
{
	gfx->y = 0;
	pix = gfx->screen->pixels;
	while (gfx->y < gfx->height)
	{
		gfx->x = 0;
		while (gfx->x < gfx->width)
		{
			color = pix[gfx->x + (gfx->y * gfx->width)];
			gfx->red = color >> 16;
			gfx->green = color >> 8;
			gfx->green = gfx->green << 24;
			gfx->green = gfx->green >> 24;
			gfx->blue = color << 24;
			gfx->blue = gfx->blue >> 24;
			gfx->red /= 1.5;
			gfx->green /= 1.6;
			gfx->blue /= 1.05;
			color = ((gfx->red&0xFF) << 16)
				| ((gfx->green&0xff) << 8) | (gfx->blue&0xFF);
			pix[gfx->x + (gfx->y * gfx->width)] = color;
			gfx->x++;
		}
		gfx->y++;
	}
}

uint32_t	fade_brightness(uint32_t color, int multiplier)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	float		redf;
	float		greenf;
	float		bluef;

	red = color >> 16;
	green = color >> 8;
	green = green << 24;
	green = green >> 24;
	blue = color << 24;
	blue = blue >> 24;
	redf = red;
	redf /= (float)(multiplier);
	greenf = green;
	greenf /= (float)(multiplier);
	bluef = blue;
	bluef /= (float)(multiplier);
	color = (((uint32_t)redf&0xFF) << 16)
		| (((uint32_t)greenf&0xff) << 8) | ((uint32_t)bluef&0xFF);
	return (color);
}

void	draw_scanlines(t_gfx *gfx, uint32_t *pix, uint32_t color)
{
	gfx->y = 0;
	pix = gfx->screen->pixels;
	while (gfx->y < gfx->height)
	{
		gfx->x = 0;
		while (gfx->x < gfx->width)
		{
			color = pix[gfx->x + (gfx->y * gfx->width)];
			gfx->red = color >> 16;
			gfx->green = color >> 8;
			gfx->green = gfx->green << 24;
			gfx->green = gfx->green >> 24;
			gfx->blue = color << 24;
			gfx->blue = gfx->blue >> 24;
			gfx->red /= 1.5;
			gfx->green /= 1.5;
			gfx->blue /= 1.4;
			color = ((gfx->red&0xFF) << 16)
				| ((gfx->green&0xff) << 8) | (gfx->blue&0xFF);
			pix[gfx->x + (gfx->y * gfx->width)] = color;
			gfx->x++;
		}
		gfx->y += (2 * gfx->scale);
	}
}
