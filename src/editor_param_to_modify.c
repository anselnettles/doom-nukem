/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_param_to_modify.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:07:59 by tturto            #+#    #+#             */
/*   Updated: 2023/03/02 19:08:00 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Selects the parameter to be modified in img2 grid.
*/

void    param_to_modify(t_map *map)
{
    if (map->param_y_to_modify == 0)
        map->param_to_modify = 0;
    else if (map->param_y_to_modify == 1)
        map->param_to_modify = 1;
    else if (map->param_y_to_modify == 2)
        map->param_to_modify = 2;
    else if (map->param_y_to_modify == 3)
        map->param_to_modify = 3;
    else if (map->param_y_to_modify == 4)
        map->param_to_modify = 4;
    else
    {
        tt_errors("param_to_modify() fail. Undefined error.");
        exit(-1);
    }
}
