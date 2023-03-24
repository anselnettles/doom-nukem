/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_filters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:40:31 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/24 17:38:37 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int		draw_lantern_glow(t_gfx *gfx, int scale)
{
	uint32_t	*color;

	color = gfx->screen->pixels;
	gfx->y = 0;
	while (gfx->y < gfx->height / 6)
	{
		gfx->x = 0;
		while (gfx->x < gfx->width / 6)
		{
			pixel_put(gfx, gfx->x, gfx->y, 0xFFFFFFFF);
				//color[((gfx->x + scale) * scale) + (gfx->y * gfx->width)]);
			gfx->x += scale;
		}
		gfx->y += scale;
	}

	return (0);
}

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
			color = ((gfx->red & 0xFF) << 16)
				| ((gfx->green & 0xff) << 8) | (gfx->blue & 0xFF);
			pix[gfx->x + (gfx->y * gfx->width)] = color;
			gfx->x++;
		}
		gfx->y++;
	}
}

uint32_t	shader(t_gfx *gfx, uint32_t color, int multiplier)
{
	float		redf;
	float		greenf;
	float		bluef;

	redf = (uint32_t)color >> 16;
	greenf = (uint32_t)color >> 8;
	greenf = (uint32_t)greenf << 24;
	greenf = (uint32_t)greenf >> 24;
	bluef = (uint32_t)color << 24;
	bluef = (uint32_t)bluef >> 24;
	redf /= (float)((gfx->lantern) * (multiplier));
	greenf /= (float)((gfx->lantern) * (multiplier));
	bluef /= (float)((gfx->lantern) * (multiplier));
	color = (((uint32_t)redf & 0xFF) << 16)
		| (((uint32_t)greenf & 0xff) << 8) | ((uint32_t)bluef & 0xFF);
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
			color = ((gfx->red & 0xFF) << 16)
				| ((gfx->green & 0xff) << 8) | (gfx->blue & 0xFF);
			pix[gfx->x + (gfx->y * gfx->width)] = color;
			gfx->x++;
		}
		gfx->y += (2 * gfx->scale);
	}
}
