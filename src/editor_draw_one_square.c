/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_one_square.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:34:06 by tturto            #+#    #+#             */
/*   Updated: 2023/02/28 17:25:16 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	draw_one_square(t_gfx *gfx, t_xy_start_end *interval)
{
	int	y;
	int	x;
	
	y = interval->y_start;
	while (y < interval->y_end)
	{
		x = interval->x_start;
		while (x < interval->x_end)
		{
			editor_pix_put(gfx, x, y, interval->colour);
			x = x + 1;
		}
		y = y + 1;
	}
}
