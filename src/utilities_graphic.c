/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_graphic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:35:22 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/14 14:26:32 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	get_wall_layer(int c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (3);
	return (0);
}

uint32_t	get_color(t_ray *ray, t_vectorif texture, int layer, t_wall wall)
{
	uint32_t	color;
	int			i;

	i = get_value(ray->map, wall.x, wall.y, 1);
	color = ray->gfx.texture[i].frame[0].pixels[texture.x
		+ ((int)texture.y * 64)];
	if (layer && ray->gfx.texture[13].frame[(layer - 1)
			+ ray->gfx.frame.algae].pixels[texture.x + ((int)texture.y * 64)])
		color = ray->gfx.texture[13].frame[(layer - 1)
			+ ray->gfx.frame.algae].pixels[texture.x + ((int)texture.y * 64)];
	return (color);
}

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

static int	draw_letter(t_gfx *gfx, int x_start, int y, int start_gfx_x)
{
	int	x;
	int	goal_x;

	goal_x = start_gfx_x + LETTER_WIDTH;
	x = x_start;
	while (gfx->y < LETTER_HEIGHT)
	{
		while (gfx->x < (goal_x))
		{
			if (gfx->texture[6].frame[0].pixels[gfx->x + (gfx->y * 728)])
			{
				if (pixel_put(gfx, x, (y + (gfx->flow_y_adjust * gfx->scale)),
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
		coordinates (x, y) of a string to be written.
*/
int	gfx_write(int x_start, int y_start, t_gfx *gfx, char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] >= ',' && s[i] <= '.') || (s[i] >= 'A' && s[i] <= 'Z')
			|| s[i] == '\'' || s[i] == '!' || s[i] == '"' || s[i] == '?')
		{
			gfx->x = s[i] * LETTER_WIDTH;
			gfx->y = 0;
			if (draw_letter(gfx, x_start, y_start, gfx->x) == ERROR)
				return (error(GFX_WRITE_ERROR));
		}
		else if (s[i] == ' ')
			x_start += LETTER_WIDTH;
		else
			return (error(GFX_WRITE_ERROR));
		i++;
		x_start += (LETTER_WIDTH * gfx->scale);
		if (s[i - 1] == 'I' || s[i - 1] == '!' || s[i - 1] == '\'')
			x_start -= 6;
	}
	return (0);
}
