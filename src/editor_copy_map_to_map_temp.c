/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_copy_map_to_map_temp.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: tturto                                   #+#    #+#             */
/*   Updated: 2023/02/19 14:02:29 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Copies ***map values to ***map_temp.
*/
void	copy_map_to_map_temp(t_drown *data)
{
	int	i0;
	int	i1;
	int	i2;

	i0 = 0;
	i1 = 0;
	i2 = 0;
	while (i2 < data->editor.images.row1)
	{
		i1 = 0;
		while (i1 < data->editor.images.column1)
		{
			i0 = 0;
			while (i0 < PARAM_COUNT)
			{
				data->map.map_temp[i2][i1][i0] = data->map.map[i2][i1][i0];
				i0++;
			}
			i1++;
		}
		i2++;
	}
}
