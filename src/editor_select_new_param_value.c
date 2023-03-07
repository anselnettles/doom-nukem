/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_select_new_param_value.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:44:30 by tturto            #+#    #+#             */
/*   Updated: 2023/03/07 18:48:13 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	Special elements
*/
static void	value_of_parameter_4(t_map *map, t_character *chars)
{
	if (map->selection_index == 0)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param4_choice0;
	else if (map->selection_index == 1)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param4_choice1;
	else if (map->selection_index == 2)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param4_choice2;
	else if (map->selection_index == 3)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param4_choice3;
	else if (map->selection_index == 4)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param4_choice4;
}

/*
	Entity
*/
static void	value_of_parameter_3(t_map *map, t_character *chars)
{
	if (map->selection_index == 0)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param3_choice0;
	else if (map->selection_index == 1)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param3_choice1;
	else if (map->selection_index == 2)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param3_choice2;
	else if (map->selection_index == 3)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param3_choice3;
	else if (map->selection_index == 4)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param3_choice4;
	else if (map->selection_index == 5)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param3_choice5;
}

/*
	"45 degree" walls
*/
static void	value_of_parameter_2(t_map *map, t_character *chars)
{
	if (map->selection_index == 0)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param2_choice0;
	else if (map->selection_index == 1)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param2_choice1;
	else if (map->selection_index == 2)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param2_choice2;
	else if (map->selection_index == 3)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param2_choice3;
	else if (map->selection_index == 4)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param2_choice4;
}

/*
	Textures
*/
static void	value_of_parameter_1(t_map *map, t_character *chars)
{
	if (map->selection_index == 0)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param1_choice0;
	else if (map->selection_index == 1)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param1_choice1;
	else if (map->selection_index == 2)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param1_choice2;
	else if (map->selection_index == 3)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param1_choice3;
}

/*
	Function overwrites map[][][X] with a pre-defined char

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
			value_of_parameter_0(&data->map, &data->editor.chars);
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->map.param_to_modify == 1)
			value_of_parameter_1(&data->map, &data->editor.chars);
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->map.param_to_modify == 2)
			value_of_parameter_2(&data->map, &data->editor.chars);
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->map.param_to_modify == 3)
			value_of_parameter_3(&data->map, &data->editor.chars);
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->map.param_to_modify == 4)
			value_of_parameter_4(&data->map, &data->editor.chars);
	}
}
