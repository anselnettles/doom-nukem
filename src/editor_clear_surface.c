/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_clear_surface.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:15:12 by tturto            #+#    #+#             */
/*   Updated: 2023/03/03 16:24:30 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	clear_surface(t_drown *data)
{
	int	x;
	int	y;

	y = 0;
	data->editor.interval.colour = 0x00000000;
	while (y < data->gfx.height - 1)
	{
		x = 0;
		while (x < data->gfx.width - 1)
		{
			editor_pix_put(&data->gfx, x, y, data->editor.interval.colour);
			x++;
		}
		y++;
	}
}
