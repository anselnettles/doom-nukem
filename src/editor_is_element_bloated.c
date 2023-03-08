/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_is_element_bloated.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:00:14 by tturto            #+#    #+#             */
/*   Updated: 2023/03/03 19:59:24 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	Checks if a full wall map element (map[][][0] == '#') is bloated with 
		unnecessary elements; should not contain anything besides a wall texture

	Return 1 on success.
	Return 0 on fail (alien inside the full wall).
*/
int	is_element_bloated(t_map *map, t_editor_images *images)
{
	int	rows_temp;
	int	cols_temp;
	int	success;

	rows_temp = 0;
	while (rows_temp < images->row1)
	{
		cols_temp = 0;
		while (cols_temp < images->column1)
		{
			success = 0;
			if (map->map[rows_temp][cols_temp][0] == '#')
				if (map->map[rows_temp][cols_temp][2] == '.')
					if (map->map[rows_temp][cols_temp][3] == '.')
						if (map->map[rows_temp][cols_temp][4] == '.')
							success = 1;
			cols_temp++;
			if (success == 0)
				break ;
		}
		if (success == 0)
			break ;
		rows_temp++;
	}
	return (success);
}
