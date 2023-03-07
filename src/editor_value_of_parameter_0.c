/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_value_of_parameter_0.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 15:51:01 by tturto            #+#    #+#             */
/*   Updated: 2023/03/06 16:06:57 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	This function is called only by select_new_param_value(t_drown *data).
		This file exists only due to norminette; functions cannot
		exceed row size 25.
*/
static void	function_split(t_map *map, t_character *chars)
{
	if (map->selection_index == 7)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice7;
	else if (map->selection_index == 8)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice8;
	else if (map->selection_index == 9)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice9;
	else if (map->selection_index == 10)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice10;
	else if (map->selection_index == 11)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice11;
}

void	value_of_parameter_0(t_map *map, t_character *chars)
{
	if (map->selection_index == 0)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice0;
	else if (map->selection_index == 1)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice1;
	else if (map->selection_index == 2)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice2;
	else if (map->selection_index == 3)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice3;
	else if (map->selection_index == 4)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice4;
	else if (map->selection_index == 5)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice5;
	else if (map->selection_index == 6)
		map->map[map->map_y][map->map_x][map->param_to_modify]
			= chars->param0_choice6;
	else
		function_split(map, chars);
}
