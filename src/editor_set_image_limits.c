/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_set_image_limits.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/02 21:41:48 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Sets limits for images. Initializes img_switch between images, whereas row/col count.
*/
void	set_image_limits(t_drown *data)
{
	data->editor.images.img1_x_min = data->gfx.width * 0.05;
	data->editor.images.img2_x_min = data->gfx.width * 0.625;
	data->editor.images.img1_x_max = data->editor.images.img2_x_min - 1;
	data->editor.images.img3_x_min = data->gfx.width * 0.78125;
	data->editor.images.img2_x_max = data->editor.images.img3_x_min - 1;
	data->editor.images.img3_x_max = data->gfx.width;
	data->editor.images.img_y_min = data->gfx.height * 0.05;
	data->editor.images.img_y_max = data->gfx.height;
	data->editor.images.img_switch = 1;
    //img2 grid has fixed column and row count. row1 and column1 will be calculated in read_map()
	data->editor.images.row2 = IMG2_PARAM_ROW;
	data->editor.images.column2 = IMG2_PARAM_COL;
    //Initial .row3 = 0. First time calculated in img3_to_gui/get_param_row
	data->editor.images.row3 = 0;
	data->editor.images.column3 = IMG3_PARAM_COL;
}
