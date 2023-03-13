/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utilities_value_of_param.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 15:55:28 by tturto            #+#    #+#             */
/*   Updated: 2023/03/13 15:56:29 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	Special elements
*/
void	value_of_parameter_4(t_map *map, t_character *chars)
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
void	value_of_parameter_3(t_map *map, t_character *chars)
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
void	value_of_parameter_2(t_map *map, t_character *chars)
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
	These functions are only called by select_new_param_value().

	Textures
*/
void	value_of_parameter_1(t_map *map, t_character *chars)
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
