/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:00:34 by aviholai          #+#    #+#             */
/*   Updated: 2023/04/06 16:23:12 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int	draw_right_arm(t_index *i, t_gfx *gfx, int s)
{
	uint32_t	*pixels;

	gfx->f = gfx->frame.right_arm;
	pixels = gfx->texture[RIGHT_ARM].frame[gfx->f].pixels;
	gfx->x = 0;
	gfx->y = 0;
	i->y = ((gfx->height - (RARM_HT * s) + MARGIN * s) + gfx->shake_y * s);
	i->x = ((gfx->width - (RARM_WTH * s) + MARGIN * s) + gfx->shake_x * s);
	while ((i->y) < (gfx->height))
	{
		while ((i->x) < (gfx->width))
		{
			if (pixels[gfx->x + (gfx->y * RARM_WTH)])
				if (pixel_put(gfx, i->x, i->y,
						pixels[gfx->x + (gfx->y * RARM_WTH)]) == ERROR)
					return (ERROR);
			i->x += s;
			gfx->x++;
		}
		i->y += s;
		gfx->y++;
		i->x = ((gfx->width - (RARM_WTH * s) + MARGIN * s) + gfx->shake_x * s);
		gfx->x = 0;
	}
	return (0);
}

static void	left_arm_pix(t_gfx *gfx, t_index *index, int x, int y)
{
	uint32_t	*pixels;

	pixels = gfx->texture[LEFT_ARM].frame[gfx->frame.bottle].pixels;
	if ((pixels[(gfx->x + x) + ((gfx->y + y) * LARM_WTH)])
		&& (pixels[(gfx->x + x) + ((gfx->y + y) * LARM_WTH)] != YELLOW))
		pixel_put(gfx, (index->x + (x * gfx->scale)),
			(index->y + (y * gfx->scale)),
			pixels[(gfx->x + x) + ((gfx->y + y) * LARM_WTH)]);
	else if (pixels[(gfx->x + x) + ((gfx->y + y) * LARM_WTH)] == YELLOW)
		if (!(gfx->lantern <= TURN_ON || gfx->lantern == TRUE))
			pixel_put(gfx, (index->x + x), (index->y + y), GRAY);
}

static void	left_arm_scale(t_index *index, t_gfx *gfx, float distance, int div)
{
	while ((gfx->y) < (LARM_HT) && (index->y) < (gfx->height))
	{
		index->x = 0;
		gfx->x = MARGIN;
		while ((gfx->x) < (LARM_WTH))
		{
			left_arm_pix(gfx, index, 0, 0);
			if ((distance < 70 && distance >= 0 && !(gfx->x % div)))
				left_arm_pix(gfx, index, 1, 0);
			if ((distance < 70 && distance >= 0 && !(gfx->y % div)))
				left_arm_pix(gfx, index, 0, 1);
			if ((distance < 70 && distance >= 0 && !(gfx->x % div)))
			{
				index->x += gfx->scale;
				left_arm_pix(gfx, index, 0, -1);
			}
			index->x += gfx->scale;
			gfx->x++;
		}
		if ((distance < 70 && distance >= 0 && !(gfx->y % div)))
			index->y += gfx->scale;
		index->y += gfx->scale;
		gfx->y++;
	}
}

static int	draw_left_arm(t_index *index, t_gfx *gfx, t_audio *audio, int s)
{
	float	distance;
	int		div;

	gfx->y = 0;
	index->y = MARGIN * s * 3;
	distance = 70;
	div = -1;

	if (gfx->nearest < 70)
	{
		while (!(Mix_Playing(6)))
		{
			if ((int)gfx->nearest % 3 == 0)
				Mix_PlayChannel(6, audio->lantern01, 0);
			if ((int)gfx->nearest % 3 == 1)
				Mix_PlayChannel(6, audio->lantern02, 0);
			if ((int)gfx->nearest % 3 == 2)
				Mix_PlayChannel(6, audio->lantern03, 0);
		}
		distance -= (gfx->nearest);
		if (distance >= 0)
			div = LARM_WTH / distance;
	}
	left_arm_scale(index, gfx, distance, div);
	return (0);
}

int	draw_player(t_drown *d)
{
	if (draw_right_arm(&d->index, &d->gfx, d->gfx.scale) == ERROR)
		return (ERROR);
	if (d->gfx.lantern == TRUE || d->gfx.lantern == TRUE + 0.1)
		if (draw_lantern_glow(&d->gfx, d->gfx.scale) == ERROR)
			return (ERROR);
	if (draw_left_arm(&d->index, &d->gfx, &d->audio, d->gfx.scale) == ERROR)
		return (ERROR);
	return (0);
}
