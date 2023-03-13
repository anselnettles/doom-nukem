/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_select_new_param_value.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:44:30 by tturto            #+#    #+#             */
/*   Updated: 2023/03/13 15:57:21 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	split_select_new_param_value(t_drown *data)
{
	if (data->gfx.event.button.button == SDL_BUTTON_LEFT
		&& data->map.param_to_modify == 2)
	{
		value_of_parameter_2(&data->map, &data->editor.chars);
		img1_img2_img3(data);
	}
	if (data->gfx.event.button.button == SDL_BUTTON_LEFT
		&& data->map.param_to_modify == 3)
	{
		value_of_parameter_3(&data->map, &data->editor.chars);
		img1_img2_img3(data);
	}
	if (data->gfx.event.button.button == SDL_BUTTON_LEFT
		&& data->map.param_to_modify == 4)
	{
		value_of_parameter_4(&data->map, &data->editor.chars);
		img1_img2_img3(data);
	}	
}

/*
	Function overwrites map[][][X] with a pre-defined char.
	"value_of_parameter_n" functions are located in
		editor_utilities_value_of_param.

	param0 = walls
	param1 = textures
	param2 = 45 degree
	param3 = entities
	param4 = specials
*/
void	select_new_param_value(t_drown *data)
{
	if (data->gfx.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->map.param_to_modify == 0)
		{
			value_of_parameter_0(&data->map, &data->editor.chars);
			img1_img2_img3(data);
		}
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->map.param_to_modify == 1)
		{
			value_of_parameter_1(&data->map, &data->editor.chars);
			img1_img2_img3(data);
		}
		split_select_new_param_value(data);
	}
}
