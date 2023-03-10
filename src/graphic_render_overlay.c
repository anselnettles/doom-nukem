/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/08 18:31:09 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int	draw_right_arm(t_index *index, t_gfx *gfx, int s)
{
	gfx->f = gfx->frame.right_arm;
	gfx->x = 0;
	gfx->y = 0;
	index->y = ((gfx->height - (RIGHT_ARM_HEIGHT * s) + MARGIN * s) + gfx->shake_y * s);
	index->x = ((gfx->width - (RIGHT_ARM_WIDTH * s) + MARGIN * s) + gfx->shake_x * s);
	while ((index->y) < (gfx->height))
	{
		while ((index->x) < (gfx->width))
		{
			if (gfx->texture[RIGHT_ARM].frame[gfx->f].pixels[gfx->x + (gfx->y * RIGHT_ARM_WIDTH)])
				if (pixel_put(gfx, index->x, index->y,
						gfx->texture[RIGHT_ARM].frame[gfx->f].pixels
						[gfx->x + (gfx->y * RIGHT_ARM_WIDTH)]) == ERROR)
					return (ERROR);
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = ((gfx->width - (RIGHT_ARM_WIDTH * s) + MARGIN * s) + gfx->shake_x * s);
		gfx->x = 0;
	}
	return (0);
}

static int	draw_left_arm(t_index *index, t_gfx *gfx, int s)
{
	gfx->f = gfx->frame.bottle;
	gfx->x = MARGIN;//gfx->shake_x;
	gfx->y = 0;//gfx->shake_y;
	index->y = MARGIN * s * 3;//((gfx->height - (238 * s) + MARGIN * s) + gfx->shake_y * s);
	index->x = 0;//((gfx->width - (250 * s) + MARGIN * s) + gfx->shake_x * s);
	while ((gfx->y) < (LEFT_ARM_HEIGHT) && (index->y) < (gfx->height))
	{
		while ((gfx->x) < (LEFT_ARM_WIDTH))
		{
			if (gfx->texture[LEFT_ARM].frame[gfx->f].pixels[gfx->x + (gfx->y * LEFT_ARM_WIDTH)])
				if (pixel_put(gfx, index->x, index->y,
						gfx->texture[LEFT_ARM].frame[gfx->f].pixels
						[gfx->x + (gfx->y * LEFT_ARM_WIDTH)]) == ERROR)
					return (ERROR);
			index->x += s;
			gfx->x++;
		}
		index->y += s;
		gfx->y++;
		index->x = 0;
		gfx->x = MARGIN;//gfx->shake_x;
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

static int	transition_wipe_black(t_index *index, t_gfx *gfx, int s, int limit)
{
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
		limit -= (s * 12);
	else if (limit <= 0)
		gfx->y += (s * 12);
	return (limit);
}

static void	draw_transition(t_drown *d, int s, int f)
{
	static int	limit = HEIGHT;
	uint32_t	*pixels;

	limit = transition_wipe_black(&d->index, &d->gfx, s, limit);
	pixels = d->gfx.texture[TRANSITION].frame[f].pixels;
	while ((d->gfx.y) < (TRANSITION_HEIGHT))
	{
		d->index.x = 0;
		d->gfx.x = 0;
		while ((d->gfx.x) < (TRANSITION_WIDTH))
		{
			if (pixels[d->gfx.x + (d->gfx.y * TRANSITION_WIDTH)]
				&& pixels[d->gfx.x + (d->gfx.y * TRANSITION_WIDTH)] != RED)
				pixel_put(&d->gfx, d->index.x, d->index.y,
					pixels[d->gfx.x + (d->gfx.y * TRANSITION_WIDTH)]);
			else if (pixels[d->gfx.x + (d->gfx.y * TRANSITION_WIDTH)] == RED)
				pixel_put(&d->gfx, d->index.x, d->index.y, BLACK);
			d->index.x += s;
			d->gfx.x++;
		}
		d->index.y += s;
		d->gfx.y++;
	}
	d->system.transition = !(limit <= 0 && d->gfx.y <= TRANSITION_HEIGHT);
}

int	render_overlay(t_drown *d)
{
	underwater_effect(d, &d->gfx, d->gfx.scale, 0);
	if (draw_right_arm(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (draw_left_arm(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (d->system.filters == TRUE)
		draw_color_filter(&d->gfx, 0, 0);
	if (d->gfx.frame.bubble >= 13)
		SDL_FillRect(d->gfx.screen, NULL, 0);
	if (render_hud(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (string_timeline(d, d->gfx.scale) == ERROR)
		return (ERROR);
	if (d->system.transition == TRUE)
		draw_transition(d, d->gfx.scale, d->gfx.frame.transition);
	if (d->system.filters == TRUE)
		draw_scanlines(&d->gfx, 0, 0);
	return (0);
}
