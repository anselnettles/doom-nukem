/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/03 15:01:05 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int	draw_right_arm(t_index *index, t_gfx *gfx, int s)
{
	gfx->f = gfx->frame.right_arm;
	gfx->x = 0;
	gfx->y = 0;
	index->y = ((gfx->height - (238 * s) + MARGIN * s) + gfx->shake_y * s);
	index->x = ((gfx->width - (250 * s) + MARGIN * s) + gfx->shake_x * s);
	while ((index->y) < (gfx->height))
	{
		while ((index->x) < (gfx->width))
		{
			if (gfx->texture[5].frame[gfx->f].pixels[gfx->x + (gfx->y * 250)])
				if (pixel_put(gfx, index->x, index->y,
						gfx->texture[5].frame[gfx->f].pixels[gfx->x + (gfx->y * 250)]) == ERROR)
					return (ERROR);
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = ((gfx->width - (250 * s) + MARGIN * s) + gfx->shake_x * s);
		gfx->x = 0;
	}
	return (0);
}

static void	underwater_effect(t_drown *d, t_gfx *gfx, int scale, int i)
{
	uint32_t	*color;
	int			toggle;
	
	color = gfx->screen->pixels;
	gfx->x = 0;
	gfx->y = 0;
	toggle = -TRUE;
	while (gfx->y < gfx->height)
	{
		while (gfx->x < gfx->width)
		{
			pixel_put(gfx, gfx->x, gfx->y,
					color[(gfx->x + i * scale) + (gfx->y * gfx->width)]);
			gfx->x += scale;
		}
		gfx->y += scale;
		gfx->x = 0;
		if ((toggle && !(gfx->y / 20 % 2)) || (!(toggle) && (gfx->y / 20) % 2))
			i -= toggle;
		if (i <= 0 || i >= 19)
			toggle = -toggle;
		if (i <= 0)
			gfx->y += 20 * scale;
	}
}

/*
static int	underwater_effect(t_drown *d, t_gfx *gfx, int scale)
{
	uint32_t	temp[10];
	uint32_t	*color;
	int			i;
	int			toggle;
	int			reverse;

	(void)scale;
	*temp = 0;
	color = gfx->screen->pixels;
	
	i = 0;//d->system.time % 2;
	toggle = FALSE;
	reverse = FALSE;
	gfx->x = 0;
	gfx->y = 0;
	while (gfx->y < gfx->height)
	{
		while (gfx->x <= gfx->width && gfx->x >= 0)
		{
			if (toggle == FALSE)
			{
				temp[i] = color[gfx->x + (gfx->y * gfx->width)];
				
				if (reverse == FALSE)		
					gfx->x += scale;
				else
					gfx->x -= scale;
			
				i++;

				if (i >= 9)
				{
					toggle = TRUE;
					i = 0;
				}
			}
			if (toggle == TRUE)
			{
				pixel_put(gfx, gfx->x, gfx->y, temp[i]);

				if (reverse == FALSE)
					gfx->x += scale;
				else
					gfx->x -= scale;

				i++;

				if (i >= 9)
				{
					toggle = FALSE;
					//i = 0;
				}
			}
		}
		if (i >= 8)
		{
			if (reverse == TRUE)
				reverse = FALSE;
			else
				reverse = TRUE;
		}
	//	else
	//	{
			//i++;
			gfx->y += scale;
			//reverse = FALSE;
	//	}
		gfx->x = 0;
		if (reverse == TRUE)
			gfx->x = gfx->width;
	}
	return (0);
}*/

int	render_overlay(t_drown *d)
{
	underwater_effect(d, &d->gfx, d->gfx.scale, 0);
	if (draw_right_arm(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (d->system.filters == TRUE)
		draw_color_filter(&d->gfx);
	if (d->gfx.frame.bubble >= 13)
		SDL_FillRect(d->gfx.screen, NULL, 0);
	if (render_hud(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (string_timeline(d) == ERROR)
		return (ERROR);
	if (d->system.filters == TRUE)
		draw_scanlines(&d->gfx);
	return (0);
}
