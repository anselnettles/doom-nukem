/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/03 16:15:37 by aviholai         ###   ########.fr       */
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
						gfx->texture[5].frame[gfx->f].pixels
						[gfx->x + (gfx->y * 250)]) == ERROR)
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
	i = d->system.time % 1000 / 500;
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

static int	draw_transition(t_index *index, t_gfx *gfx, int s, int f)
{
	static int	limit = HEIGHT;
	
	index->y = 0;
	while (index->y < (limit * s))
	{
		index->x = 0;
		while (index->x < gfx->width)
		{
			pixel_put(gfx, index->x, index->y, 0);
			index->x += s;
		}
		index->y += s;
	}

	gfx->y = 0;
	if (limit > 0)
		limit -= (s * 8);
	else if (limit <= 0 && gfx->y > 0)
		gfx->y -= (s * 8);



	while ((gfx->y) < (TRANSITION_HEIGHT))
	{
		index->x = 0;
		gfx->x = 0;
		while ((gfx->x) < (TRANSITION_WIDTH))
		{
			if (gfx->texture[TRANSITION].frame[f].pixels
				[gfx->x + (gfx->y * TRANSITION_WIDTH)] && gfx->texture[TRANSITION].frame[f].pixels
				[gfx->x + (gfx->y * TRANSITION_WIDTH)] != 65535)
				pixel_put(gfx, index->x, index->y,
						gfx->texture[TRANSITION].frame[f].pixels
						[gfx->x + (gfx->y * TRANSITION_WIDTH)]);
			else if (gfx->texture[TRANSITION].frame[f].pixels
					[gfx->x + (gfx->y * TRANSITION_WIDTH)] == 65535)
				pixel_put(gfx, index->x, index->y, 0x000000);
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
	}

//	if (finished)
//	{
//		return (EXIT);
//	}
	return (FALSE);
}

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
	if (d->system.transition == TRUE)
		if (draw_transition(&d->index, &d->gfx, d->gfx.scale, d->gfx.frame.transition) == EXIT)
			d->system.transition == FALSE;
	if (d->system.filters == TRUE)
		draw_scanlines(&d->gfx);
	return (0);
}
