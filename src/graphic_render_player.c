/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_player.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 17:00:34 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/12 17:07:55 by aviholai         ###   ########.fr       */
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

static void	left_arm_pix(t_gfx *gfx, t_index *index, int x, int y)
{
	uint32_t	*pixels;

	pixels = gfx->texture[LEFT_ARM].frame[gfx->frame.bottle].pixels;
	if ((pixels[(gfx->x + x) + ((gfx->y + y) * LEFT_ARM_WIDTH)]) && (pixels[(gfx->x + x) + ((gfx->y + y) * LEFT_ARM_WIDTH)] != YELLOW))
		pixel_put(gfx, (index->x + (x * gfx->scale)), (index->y + (y * gfx->scale)), pixels[(gfx->x + x) + ((gfx->y + y) * LEFT_ARM_WIDTH)]);
	else if (pixels[(gfx->x + x) + ((gfx->y + y) * LEFT_ARM_WIDTH)] == YELLOW)
		pixel_put(gfx, (index->x + x), (index->y + y), GRAY);
}

static int	draw_left_arm(t_index *index, t_gfx *gfx, int f, int s)
{
	uint32_t	*pixels;
	float			variable = 70;
	int				space = -1;

	pixels = gfx->texture[LEFT_ARM].frame[f].pixels;
	gfx->x = MARGIN;//gfx->shake_x;
	gfx->y = 0;//gfx->shake_y;
	index->y = MARGIN * s * 3;//((gfx->height - (238 * s) + MARGIN * s) + gfx->shake_y * s);
	index->x = 0;//((gfx->width - (250 * s) + MARGIN * s) + gfx->shake_x * s);

	if (gfx->nearest < 70)
	{
		variable -= gfx->nearest;
		if (variable >= 0)
			space = LEFT_ARM_WIDTH / variable;
	}
	while ((gfx->y) < (LEFT_ARM_HEIGHT) && (index->y) < (gfx->height))
	{
		while ((gfx->x) < (LEFT_ARM_WIDTH))
		{
			left_arm_pix(gfx, index, 0, 0);
			if ((variable < 70 && variable >= 0 && !(gfx->x % space)))
				left_arm_pix(gfx, index, 1, 0);
			if ((variable < 70 && variable >= 0 && !(gfx->y % space)))
				left_arm_pix(gfx, index, 0, 1);
			if ((variable < 70 && variable >= 0 && !(gfx->x % space)))
			{
				index->x += s;
				left_arm_pix(gfx, index, 0, -1);
			}
			index->x += s;
			gfx->x++;
		}
		if ((variable < 70 && variable >= 0 && !(gfx->y % space)))
		{
			index->y += s;
		}
		index->y += s;
		gfx->y++;
		index->x = 0;
		gfx->x = MARGIN;//gfx->shake_x;
	}
	return (0);
}

int	draw_player(t_index *index, t_gfx *gfx)
{
	if (draw_right_arm(index, gfx, gfx->scale) == ERROR)
		return (ERROR);
	if (draw_left_arm(index, gfx, gfx->frame.bottle, gfx->scale) == ERROR)
		return (ERROR);
	return (0);
}
