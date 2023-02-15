/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_filters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:40:31 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/10 17:42:14 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	draw_color_filter(t_gfx *gfx)
{
	int	y;
	int	x;
	x = 0;
	y = 0;
	uint32_t	*pix;
	uint32_t	color;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	pix = gfx->screen->pixels;
	while (y < gfx->height)
	{
		while (x < gfx->width)
		{
			color = pix[x + (y * gfx->width)];
			red = color >> 16;
			green = color >> 8;
			green = green << 24;
			green = green >> 24;
			blue = color << 24;
			blue = blue >> 24;
			red /= 1.8;
			green /= 2.2;
			blue /= 1.2;
			color = ((red&0xFF) << 16) | ((green&0xff) << 8) | (blue&0xFF);
			pix[x + (y * gfx->width)] = color;
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_scanlines(t_gfx *gfx)
{
	int	y;
	int	x;
	x = 0;
	y = 0;
	uint32_t	*pix;
	uint32_t	color;
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;

	pix = gfx->screen->pixels;
	while (y < gfx->height)
	{
		while (x < gfx->width)
		{
			color = pix[x + (y * gfx->width)];
			red = color >> 16;
			green = color >> 8;
			green = green << 24;
			green = green >> 24;
			blue = color << 24;
			blue = blue >> 24;
			red /= 1.5;
			green /= 1.5;
			blue /= 1.4;
			color = ((red&0xFF) << 16) | ((green&0xff) << 8) | (blue&0xFF);
			pix[x + (y * gfx->width)] = color;
			x++;
		}
		x = 0;
		y += (2 * gfx->scale);
	}
}