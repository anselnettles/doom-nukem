/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_overlay.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:08:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/17 11:10:30 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

static void	droplet(t_rain *r, int x, int y)
{
	pixel_put(&r->graph, x, y, 0xC1BCCB);
	pixel_put(&r->graph, x, y + 2, 0xC1BCCB);
	pixel_put(&r->graph, x, y + 4, 0xC1BCCB);
	pixel_put(&r->graph, x, y + 6, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 7, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 8, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 9, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 10, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 11, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 12, 0xD4D0DE);
	pixel_put(&r->graph, x, y + 13, 0xD4D0DE);
}

void	draw_overlay(t_rain *r)
{
	static int	y[24] = {10, 90, 50, 180, 80, 250, 140, 320, 220, 150,
		30, 40, 32, 450, 23, 53, 423, 54, 4, 12, 234, 123, 153, 231};
	static int	x[24] = {10, 90, 20, 80, 30, 70, 40, 60, 50, 110, 120,
		32, 323, 123, 431, 12, 43, 54, 76, 94, 37, 64, 12, 43};
	int			i;

	i = 0;
	while (i++ < 24)
		droplet(r, x[i], y[i]++);
	i = 0;
	while (i++ < 24)
	{
		if (y[i] >= 465)
		{
			y[i] = 0;
			x[i] = rand() % 639 + 1;
		}
	}
}
