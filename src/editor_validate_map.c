/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_validate_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:27:03 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 18:41:27 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	The called functions are located as non-static
		in editor_utilities_param_check.c
*/
static int	i0_checker(t_drown *data, t_index *i, int i0)
{
	if (i0 == 0 && (i0_is_0(data, i, i0) != 1))
		return (0);
	else if (i0 == 1 && (i0_is_1(data, i, i0) != 1))
		return (0);
	else if (i0 == 2 && (i0_is_2(data, i, i0) != 1))
		return (0);
	else if (i0 == 3 && (i0_is_3(data, i, i0) != 1))
		return (0);
	else if (i0 == 4 && (i0_is_4(data, i, i0) != 1))
		return (0);
	return (1);
}

/*
    Validates char ***map; whether it follows the pre-defined standard or not.

    Return value: 1 on success, 0 on fail
*/
int	validate_map(t_drown *data)
{
	t_index	i;

	i = (t_index){.i0 = 0, .i1 = 0, .i2 = 0};
	while (i.i2 < data->editor.images.row1)
	{
		i.i1 = 0;
		while (i.i1 < data->editor.images.column1)
		{
			i.i0 = 0;
			while (i.i0 < PARAM_COUNT)
			{
				if (i0_checker(data, &i, i.i0) != 1)
				{
					tt_errors("validate_map() fail.");
					return (0);
				}
				i.i0++;
			}
			i.i1++;
		}
		i.i2++;
	}
	return (1);
}
