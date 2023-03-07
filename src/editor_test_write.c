/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_test_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/07 19:07:17 by tturto           ###   ########.fr       */
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
static int	test_pixel_put(t_gfx *gfx, int x, int y, uint32_t color)
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

static int	test_draw_letter(t_gfx *gfx, int x_start, int y_start, int start_gfx_x)
{
	int	y;
	int	x;

	int goal_x;                             //was moved here from function arguments
	goal_x = start_gfx_x + LETTER_WIDTH;    //goal_x formerly called as (gfx->x + LETTER_WIDTH) | note that start_gfx_x = gfx->x  

	x = x_start;
	y = y_start;
	while (gfx->y < LETTER_HEIGHT)
	{
		while (gfx->x < (goal_x))
		{
			if (gfx->texture[6].frame[0].pixels[gfx->x + (gfx->y * 728)])
			{
				if (test_pixel_put(gfx, x, (y + (gfx->flow_y_adjust * gfx->scale)),
						gfx->texture[6].frame[0].pixels
						[gfx->x + (gfx->y * 728)]) == ERROR)
					return (ERROR);
			}
			x += (gfx->scale);
			gfx->x++;
		}
		y += (gfx->scale);
		gfx->y++;
		x = x_start;
		gfx->x = start_gfx_x;
	}
	return (0);
}

/*
	This is a modified versions to ami's gfx_write(), to include start
		coordinates (x, y) of a string write.
*/
int editor_test_write(t_gfx *gfx, char *s, int x_start, int y_start)
{
	int	i;
	int	x;
	int y;

	i = 0;
	x = x_start;
	y = y_start;
	while (s[i] != '\0')
	{
		if ((s[i] >= ',' && s[i] <= '.') || (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '\'' || s[i] == '!' || s[i] == '"' || s[i] == '?')
		{
			gfx->x = s[i] * LETTER_WIDTH;
			gfx->y = 0;
			if (test_draw_letter(gfx, x, y, gfx->x) == ERROR)
				return (error(GFX_WRITE_ERROR));
		}
		else if (s[i] == ' ')
			x += LETTER_WIDTH;
		else
			return (error(GFX_WRITE_ERROR));
		i++;
		x += (LETTER_WIDTH * gfx->scale);
		if (s[i - 1] == 'I' || s[i - 1] == '!' || s[i - 1] == '\'')
			x -= 6;
	}
	return (0);
}
