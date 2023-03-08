/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_validate_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:27:03 by tturto            #+#    #+#             */
/*   Updated: 2023/03/07 18:51:30 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int  i0_checker(t_drown *data, t_index *i, int i0)
{
    if (i0 == 0)
    {
        if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice0 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice1
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice2 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice3
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice4 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice5
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice6 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice7
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice8 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice9
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice10 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param0_choice11)
            {
                printf("i0_check fail i == 0 | i->i2 %d, i->i1 %d\n", i->i2, i->i1);   //remove every "i0_check printf"
                return (0);
            }      
    }
    else if (i0 == 1)
    {
        if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice0 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice1
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice2 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param1_choice3)
            {
                printf("i0_check fail i == 1 | i->i2 %d, i->i1 %d\n", i->i2, i->i1);
                return (0);
            }
    }
    else if (i0 == 2)
    {
        if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice0 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice1
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice2 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice3
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param2_choice4)
            {
                printf("i0_check fail i == 2 | i->i2 %d, i->i1 %d\n", i->i2, i->i1);
                return (0);
            }
    }
    else if (i0 == 3)
    {
        if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice0 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice1
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice2 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice3
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice4 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param3_choice5)
            {
                printf("i0_check fail i == 3 | i->i2 %d, i->i1 %d\n", i->i2, i->i1);
                return (0);
            }
    }
    else if (i0 == 4)
    {
         if (data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice0 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice1
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice2 && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice3
            && data->map.map[i->i2][i->i1][i0] != data->editor.chars.param4_choice4)
            {
                printf("i0_check fail i == 4 | i->i2 %d, i->i1 %d\n", i->i2, i->i1);
                return (0);
            }
    }
    return (1);
}

/*
    Validates char ***map_temp; whether it follows the pre-defined standard or not.

    Return value: 1 on success, 0 on fail
*/
int validate_map(t_drown *data)
{
    t_index i;

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
                    tt_errors("validate_map_temp: i0_checker fail. False map element not specified.");
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
