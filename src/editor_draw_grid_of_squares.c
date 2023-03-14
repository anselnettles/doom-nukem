/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_draw_grid_of_squares.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 19:13:30 by tturto            #+#    #+#             */
/*   Updated: 2023/03/14 17:50:36 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    param_to_modify(0)	= walls
    param_to_modify(1)	= textures
    param_to_modify(2)	= "45 degree" walls
    param_to_modify(3)	= entities
    param_to_modify(4)	= specials
*/
static void	get_param_row3(t_editor_images *images, t_map *map)
{
	if (map->param_to_modify == 0)
		images->row3 = 12;
	else if (map->param_to_modify == 1)
		images->row3 = 4;
	else if (map->param_to_modify == 2)
		images->row3 = 5;
	else if (map->param_to_modify == 3)
		images->row3 = 6;
	else if (map->param_to_modify == 4)
		images->row3 = 5;
}

static void	get_col_row_max(t_drown *data, int *row_max,
	int *col_max, int image_switch)
{
	if (image_switch == 1)
	{
		*row_max = data->editor.images.row1;
		*col_max = data->editor.images.column1;
	}
	else if (image_switch == 2)
	{
		*row_max = IMG2_PARAM_ROW;
		*col_max = IMG2_PARAM_COL;
	}
	else if (image_switch == 3)
	{
		*row_max = data->editor.images.row3;
		*col_max = IMG3_PARAM_COL;
	}
}

static void	one_square_data(t_drown *data, int *row_now, int *col_now,
	int cathetus)
{
	data->editor.interval.colour = element_colour(&data->map, *row_now,
			*col_now, data->editor.images.img_switch);
	draw_one_square(&data->gfx, &data->editor.interval);
	(*col_now)++;
	data->editor.interval.x_start = data->editor.interval.x_end + 2;
	data->editor.interval.x_end = data->editor.interval.x_start
		+ (cathetus - 1);
}

/*
    Insert comments
	...
	cat = cathetus
*/
static void	draw_grid_of_squares_mod(t_drown *data, int cat, int img_x_min)
{
	t_row_col	rc;

	rc = (t_row_col){.row_now = 0, .col_now = 0, .row_max = 0, .col_max = 0};
	if (data->editor.images.img_switch == 3)
		get_param_row3(&data->editor.images, &data->map);
	get_col_row_max(data, &rc.row_max, &rc.col_max,
		data->editor.images.img_switch);
	data->editor.interval.y_start = data->editor.images.img_y_min;
	data->editor.interval.y_end = data->editor.interval.y_start + cat;
	while (rc.row_now < rc.row_max)
	{
		rc.col_now = 0;
		data->editor.interval.x_start = img_x_min;
		if (data->editor.images.img_switch == 3)
			data->editor.interval.x_end = data->editor.interval.x_start
				+ (2 * cat - 1);
		else
			data->editor.interval.x_end = data->editor.interval.x_start
				+ (cat - 1);
		while (rc.col_now < rc.col_max)
			one_square_data(data, &rc.row_now, &rc.col_now, cat);
		rc.row_now++;
		data->editor.interval.y_start = data->editor.interval.y_end + 2;
		data->editor.interval.y_end = data->editor.interval.y_start + (cat - 1);
	}
}

/*
    Insert comments
*/
void	draw_grid_of_squares(t_drown *data)
{
	gfx_write(data->editor.images.img1_x_min, data->gfx.height * 0.7,
		&data->gfx, "MOUSE-ONE TO SELECT AN ELEMENT");
	gfx_write(data->editor.images.img1_x_min, data->gfx.height * 0.72,
		&data->gfx, "MOUSE-TWO TO CLOSE SELECTION COLUMNS");
	gfx_write(data->editor.images.img1_x_min, data->gfx.height * 0.76,
		&data->gfx, "Z TO PLAY");
	if (data->editor.images.img_switch == 1)
		draw_grid_of_squares_mod(data, IMG1_CATHETUS,
			data->editor.images.img1_x_min);
	else if (data->editor.images.img_switch == 2)
		draw_grid_of_squares_mod(data, IMG2_CATHETUS,
			data->editor.images.img2_x_min);
	else if (data->editor.images.img_switch == 3)
		draw_grid_of_squares_mod(data, IMG3_CATHETUS,
			data->editor.images.img3_x_min);
}
