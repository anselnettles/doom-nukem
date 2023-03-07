/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_validate_outer_walls.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 22:32:23 by tturto            #+#    #+#             */
/*   Updated: 2023/03/03 18:31:28 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Checks if mapfile is surrounded by walls.

    Return 1 on success.
    Return 0 on fail (not surrounded by walls).
*/
int	validate_outer_walls(t_map *map, t_editor_images *images)
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
				{
					tt_errors("The outermost map elements are not walls.");
					return (0);
				}
				cols_temp++;
			}
		}
		else if (map->map[rows_temp][0][0] != '#'
			|| map->map[rows_temp][images->column1 - 1][0] != '#')
		{
			tt_errors("The outermost elements of the mapfile are not walls.");
			return (0);
		}
		rows_temp++;
	}
	return (1);
}
