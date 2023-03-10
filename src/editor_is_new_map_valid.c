/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_is_new_map_valid.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:07:28 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 14:18:26 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	Checks if map[][][] contains the valid amount of
		Start and Goal elements.

	Return 1 on success.
	Return 0 on fail (either Start or Goal != 1).
*/
static int	valid_entities(t_map *map, t_editor_images *images)
{
	t_index	i;
	int		one_start_found;
	int		one_goal_found;

	i = (t_index){.i0 = 0, .i1 = 0, .i2 = 0};
	one_start_found = 0;
	one_goal_found = 0;
	while (i.i2 < images->row1)
	{
		i.i1 = 0;
		while (i.i1 < images->column1)
		{
			if (map->map[i.i2][i.i1][3] == 'X')
				one_start_found++;
			if (map->map[i.i2][i.i1][3] == 'Z')
				one_goal_found++;
			i.i1++;
		}
		i.i2++;
	}
	if (one_start_found != 1 || one_goal_found != 1)
		return (0);
	return (1);
}

/*
	Checks if a full wall map element (map[][][0] == '#') is bloated with 
		unnecessary entities; full wall should not contain an entity.

	Return 1 on success.
	Return 0 on fail.
*/
static int	is_element_bloated(t_map *map, t_editor_images *images)
{
	int	rows_temp;
	int	cols_temp;
	int	success;

	rows_temp = 0;
	success = 1;
	while (rows_temp < images->row1)
	{
		cols_temp = 0;
		while (cols_temp < images->column1)
		{
			if (map->map[rows_temp][cols_temp][0] == '#')
				if (map->map[rows_temp][cols_temp][3] != '.')
					success = 0;
			if (success == 0)
				break ;
			cols_temp++;
		}
		if (success == 0)
			break ;
		rows_temp++;
	}
	return (success);
}

/*
    Checks if mapfile is surrounded by walls.

    Return 1 on success.
    Return 0 on fail (not surrounded by walls).
*/
static int	validate_outer_walls(t_map *map, t_editor_images *images)
{
	int	rows_temp;
	int	cols_temp;

	rows_temp = 0;
	while (rows_temp < images->row1)
	{
		if (rows_temp == 0 || rows_temp == (images->row1 - 1))
		{
			cols_temp = 0;
			while (cols_temp < images->column1)
			{
				if (map->map[rows_temp][cols_temp][0] != '#')
					return (0);
				cols_temp++;
			}
		}
		else if (map->map[rows_temp][0][0] != '#'
			|| map->map[rows_temp][images->column1 - 1][0] != '#')
			return (0);
		rows_temp++;
	}
	return (1);
}

int	is_new_map_valid(t_map *map, t_editor_images *images)
{
	if (validate_outer_walls(map, images) != 1)
	{
		tt_errors("The outermost map elements are not walls.");
		return (0);
	}
	if (is_element_bloated(map, images) != 1)
	{
		tt_errors("Bloated element.");
		return (0);
	}
	if (valid_entities(map, images) != 1)
	{
		tt_errors("Map must contain only one Start and Goal.");
		return (0);
	}
	else
		return (1);
}
