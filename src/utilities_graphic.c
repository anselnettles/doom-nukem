/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/09 17:32:28 by aviholai         ###   ########.fr       */
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

	if (x > gfx->width - 1 || y > gfx->height - 1)
		return (ERROR);
	pix = gfx->screen->pixels;
	wth = gfx->width;
	pix[(x) + (y * wth)] = color << ((gfx->scanline * 0xFFFFFFFF) * (y % 2));
	if (gfx->scale >= 2 && !(x > gfx->width - 2 || y > gfx->height - 2))
	{
		pix[(x + 1) + ((y) * wth)] = color << ((gfx->scanline * 0xFFFFFFFF) * (y % 2));
		pix[(x) + ((y + 1) * wth)] = color;
		pix[(x + 1) + ((y + 1) * wth)] = color;
	}
	return (0);
}


int	draw_letter(t_gfx *gfx, int x)
{
	int	y;
	int	temp_y;

	y = ((gfx->height / 4) * 3);
	x += (gfx->width / 4);
	//goal_y = gfx->y + LETTER_HEIGHT;
	goal_x = gfx->x + LETTER_WIDTH;
	while (gfx->y)
	{
		while (gfx->x < goal_x)
		{
			if (gfx->sprite.letters[gfx->y][gfx->x])
			{
				if (pixel_put(gfx, x, y,
							gfx->sprite.letters[gfx->y][gfx->x]) == ERROR)
					return (ERROR);
			}
			x += (gfx->scale);
			gfx->x++;
		}
		y += (gfx->scale);
		gfx->y++;
		x = (gfx->width / 4);
		gfx->x = 0;
	}
	return (0);
}

int	gfx_write(t_gfx *gfx, char *str)
{
	int	i;
	int	x;

	i = 0;
	x= 0;
	while(str[i] != '\0')
	{
		if ((str[i] >= ',' && str[i] <= '.') || (str[i] >= 'A' && str[i] <= 'Z')
				|| str[i] == ' ' || str[i] == '!')
		{
			gfx->x = str[i] * LETTER_WIDTH;
			gfx->y = 0;
			if (draw_letter(gfx, x) == ERROR)
				return (error(GFX_WRITE_ERROR));
		}
		else
			return (error(GFX_WRITE_ERROR);
		i++;
		x += LETTER_WIDTH;
	}
	return (0);
}
