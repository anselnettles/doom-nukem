/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_img2_texts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 14:10:11 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 14:21:31 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	img2_texts(t_drown *data)
{
	int	x;
	int	y;
	int	step;

	x = data->editor.images.img2_x_min + IMG2_CATHETUS * 0.1;
	y = data->editor.images.img_y_min + IMG2_CATHETUS / 2;
	step = IMG2_CATHETUS + 1;
	gfx_write(x, y, &data->gfx, "WALL");
	y = y + step;
	gfx_write(x, y, &data->gfx, "TEXT.");
	y = y + step;
	gfx_write(x, y, &data->gfx, "DEG.");
	y = y + step;
	gfx_write(x, y, &data->gfx, "ENTITY");
	y = y + step;
	gfx_write(x, y, &data->gfx, "SPEC.");
}
