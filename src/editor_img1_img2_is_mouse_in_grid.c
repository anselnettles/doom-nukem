/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_img1_img2_is_mouse_in_grid.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: tturto                                   #+#    #+#             */
/*   Updated: 2023/02/19 14:00:59 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Count column/row of grid in img1 or img2.
*/
static void	get_row_and_column_count(int cathetus, t_editor_images *images, int *col_count, int *row_count)
{
	if (cathetus == IMG1_CATHETUS)
	{
		*col_count = images->column1;
		*row_count = images->row1;
	}
	else if (cathetus == IMG2_CATHETUS)
	{
		*col_count = images->column2;
		*row_count = images->row2;
	}
}

/*
 * Checks if mouse coordinates are inside the grid of img3.
 * 'Cat' stands for "cathetus".
*/
static int	is_mouse_in_grid(t_drown *d, unsigned short int img_switch, int cat)
{
	int	x;
	int	y;
	int	col_count;
	int	row_count;

	if (img_switch == 1)
	{
		x = d->editor.mouse.x - d->editor.images.img1_x_min;
		y = d->editor.mouse.y - d->editor.images.img_y_min;
		d->map.map_x = (x - (x % (cat + 1))) / (cat + 1);
		d->map.map_y = (y - (y % (cat + 1))) / (cat + 1);
	}
	else if (img_switch == 2)
	{
		x = d->editor.mouse.x - d->editor.images.img2_x_min;
		y = d->editor.mouse.y - d->editor.images.img_y_min;
		d->map.param_x_to_modify = (x - (x % (cat + 1))) / (cat + 1);
		d->map.param_y_to_modify = (y - (y % (cat + 1))) / (cat + 1);
	}
	get_row_and_column_count(cat, &d->editor.images, &col_count, &row_count);
	if (img_switch == 1 && (d->map.map_x < col_count
			&& d->map.map_y < row_count))
		return (1);
	else if (img_switch == 2 && (d->map.param_x_to_modify < col_count
			&& d->map.param_y_to_modify < row_count))
		return (1);
	return (0);
}

/*
 * Checks if mouse coordinates are in img1 or img2.
*/
static int	is_mouse_in_image(t_mouse *mouse, t_editor_images *images, unsigned short int img_switch)
{
	if (img_switch == 1
		&& (mouse->x >= images->img1_x_min && mouse->x < images->img1_x_max)
		&& (mouse->y > images->img_y_min))
		return (1);
	if (img_switch == 2
		&& (mouse->x >= images->img2_x_min && mouse->x < images->img2_x_max)
		&& (mouse->y > images->img_y_min))
		return (1);
	return (0);
}

/*
    Checks if mouse coordinates are in either in the grid of img1 or img2.
*/
int	img1_img2_is_mouse_in_grid(t_drown *data)
{
	if ((is_mouse_in_image(&data->editor.mouse, &data->editor.images,
				data->editor.images.img_switch) == 1)
		&& data->editor.images.img_switch == 1)
	{
		if (is_mouse_in_grid(data,
				data->editor.images.img_switch, IMG1_CATHETUS) == 1)
			return (1);
	}
	else if ((is_mouse_in_image(&data->editor.mouse,
				&data->editor.images, data->editor.images.img_switch) == 1)
		&& data->editor.images.img_switch == 2)
	{
		if (is_mouse_in_grid(data,
				data->editor.images.img_switch, IMG2_CATHETUS) == 1)
			return (1);
	}
	return (0);
}
