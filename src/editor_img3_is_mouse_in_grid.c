/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_img3_is_mouse_in_grid.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:43:05 by tturto            #+#    #+#             */
/*   Updated: 2023/03/03 17:43:50 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Count column/row of grid in img3.
*/
static void	get_row_and_column_count(int cathetus, t_editor_images *images,
	int *col_count, int *row_count)
{
	if (cathetus == IMG3_CATHETUS)
	{
		*col_count = images->column3;
		*row_count = images->row3;
	}
}

/*
    Checks if mouse coordinates are inside the grid of img3.
*/
static int	is_mouse_in_grid(t_drown *data,
	unsigned short int img_switch, int cathetus)
{
	int	x;
	int	y;
	int	col_count;
	int	row_count;

	x = 0;
	y = 0;
	if (img_switch == 3)
	{
		x = data->editor.mouse.x - data->editor.images.img3_x_min;
		y = data->editor.mouse.y - data->editor.images.img_y_min;
	}
	data->map.selection_x = (x - (x % (cathetus + 1))) / (cathetus + 1);
	data->map.selection_y = (y - (y % (cathetus + 1))) / (cathetus + 1);
	get_row_and_column_count(cathetus, &data->editor.images,
		&col_count, &row_count);
	if (data->map.selection_x < col_count
		&& data->map.selection_y < row_count)
		return (1);
	return (0);
}

/*
    Checks if mouse coordinates are in img3.
*/
static int	is_mouse_in_image(t_mouse *mouse, t_editor_images *images,
	unsigned short int img_switch)
{
	if (img_switch == 3 && (mouse->x >= images->img3_x_min
			&& mouse->x < images->img3_x_max) && (mouse->y > images->img_y_min))
		return (1);
	return (0);
}

/*
    Checks if mouse click is inside img3 grid.
    Updates the clicked parameter choice (selection_x and selection_y).

    Return: 1 on success, 0 on fail
*/
int	img3_is_mouse_in_grid(t_drown *data)
{
	if ((is_mouse_in_image(&data->editor.mouse, &data->editor.images,
				data->editor.images.img_switch) == 1)
		&& data->editor.images.img_switch == 3)
	{
		if (is_mouse_in_grid(data, data->editor.images.img_switch,
				IMG3_CATHETUS) == 1)
			return (1);
	}
	return (0);
}
