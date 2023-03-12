/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_get_player_start.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 16:42:49 by tturto            #+#    #+#             */
/*   Updated: 2023/03/12 17:43:21 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int	value_to_send(int row, int col, char axis)
{
	if (axis == 'x')
		return (col * BITS);
	else if (axis == 'y')
		return (row * BITS);
	return (0);
}

/*
	Returns the value of x- or y-axis. "char axis" determines
		which axis value is return.	
*/
int	get_player_start(t_map *map, t_editor_images *images, char axis)
{
	int	row;
	int	col;
	int	start_found;

	row = 0;
	start_found = 0;
	while (row < images->row1)
	{
		col = 0;
		while (col < images->column1)
		{
			if (map->map[row][col][3] == 'X')
			{
				start_found = 1;
				break ;
			}
			col++;
		}
		if (start_found == 1)
			break ;
		row++;
	}
	return (value_to_send(row, col, axis));
}
