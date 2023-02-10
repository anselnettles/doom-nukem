/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/10 14:47:19 by aviholai         ###   ########.fr       */
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
int	pixel_put(t_gfx *gfx, int x, int y, uint32_t color)
{
	uint32_t	*pix;
	int			wth;

	if (x > gfx->width - 1 || y > gfx->height - 1 || x < 0 || y < 0)
		return (ERROR);
	pix = gfx->screen->pixels;
	wth = gfx->width;
	pix[(x) + (y * wth)] = color;
	if (gfx->scale >= 2 && !(x > gfx->width - 2 || y > gfx->height - 2))
	{
		pix[(x + 1) + (y * wth)] = color;
		pix[(x) + ((y + 1) * wth)] = color;
		pix[(x + 1) + ((y + 1) * wth)] = color;
	}
	return (0);
}

void	draw_scanlines(t_gfx *gfx)
{
	int	y;
	int	x;
	x = 0;
	y = 0;
	uint32_t	*pix;
	uint32_t	color;

	pix = gfx->screen->pixels;
	while (y < gfx->height)
	{
		while (x < gfx->width)
		{
			color = pix[x + (y * gfx->width)];
			pix[x + (y * gfx->width)] = 0;
			x++;
		}
		x = 0;
		y += (2 * gfx->scale);
	}
}

int	draw_letter(t_gfx *gfx, int start_x, int goal_x)
{
	int	y;
	int	x;
	int	start_gfx_x;

	x = start_x;
	y = ((gfx->height / 4) * 3);
	start_gfx_x = gfx->x;
	while (gfx->y < LETTER_HEIGHT)
	{
		while (gfx->x < (goal_x))
		{
			if (gfx->sprite.letters[gfx->y][gfx->x])
			{
				if (pixel_put(gfx, x, (y + (gfx->flow_y_adjust * gfx->scale)),
							gfx->sprite.letters[gfx->y][gfx->x]) == ERROR)
					return (ERROR);
			}
			x += (gfx->scale);
			gfx->x++;
		}
		y += (gfx->scale);
		gfx->y++;
		x = start_x;
		gfx->x = start_gfx_x;
	}
	return (0);
}

int	gfx_write(t_gfx *gfx, char *s)
{
	int	i;
	int	x;

	i = 0;
	x = gfx->width / 6;
	while(s[i] != '\0')
	{
		if ((s[i] >= ',' && s[i] <= '.') || (s[i] >= 'A' && s[i] <= 'Z')
				|| s[i] == '\'' || s[i] == '!' || s[i] == '"' || s[i] == '?')
		{
			gfx->x = s[i] * LETTER_WIDTH;
			gfx->y = 0;
			if (draw_letter(gfx, x, (gfx->x + LETTER_WIDTH)) == ERROR)
				return (error(GFX_WRITE_ERROR));
		}
		else if (s[i] == ' ')
			x += LETTER_WIDTH;
		else
			return (error(GFX_WRITE_ERROR));
		i++;
		x += (LETTER_WIDTH * gfx->scale);
		if (s[i - 1] == 'I' || s[i - 1] == '!')
			x -= 6;
	}
	return (0);
}
