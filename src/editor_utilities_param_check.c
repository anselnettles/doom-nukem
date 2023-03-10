/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utilities_param_check.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:40:46 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 16:42:55 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	These functions are only called by validate_map()/i0_checker().
*/
int	i0_is_4(t_drown *data, t_index *i, int i0)
{
	if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice0
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice1
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice2
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice3
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice4)
	{
		tt_errors("validate_map(): i0_is_4() fail.");
		return (0);
	}
	return (1);
}

int	i0_is_3(t_drown *data, t_index *i, int i0)
{
	if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice0
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice1
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice2
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice3
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice4
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice5)
	{
		tt_errors("validate_map(): i0_is_3() fail.");
		return (0);
	}
	return (1);
}

int	i0_is_2(t_drown *data, t_index *i, int i0)
{
	if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice0
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice1
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice2
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice3
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice4)
	{
		tt_errors("validate_map(): i0_is_2() fail.");
		return (0);
	}	
	return (1);
}

int	i0_is_1(t_drown *data, t_index *i, int i0)
{
	if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice0
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice1
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice2
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice3)
	{
		tt_errors("validate_map(): i0_is_1() fail.");
		return (0);
	}
	return (1);
}

int	i0_is_0(t_drown *data, t_index *i, int i0)
{
	if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice0
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice1
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice2
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice3
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice4
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice5
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice6
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice7
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice8
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice9
		&& data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice10
		&& data->map.map[i->i2][i->i1][i0]
		!= data->editor.chars.param0_choice11)
	{
		tt_errors("validate_map(): i0_is_0() fail.");
		return (0);
	}
	return (1);
}
