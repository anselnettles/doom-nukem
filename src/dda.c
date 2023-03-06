/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 00:24:32 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/06 16:33:25 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

float   absf(float value)
{
    if (value < 0)
        return (-value);
    return(value);
}

void    algo_dda(t_ray *ray, t_wall *wall, t_dda *dda)
{
    int     collx;
    int     colly;

    collx = 32;
    colly = 32;
    if (wall->dx > 0)
        collx = 31;
    if (wall->dy > 0)
        colly = 31;
    dda->hit = 0;
    wall->side = 0;
    while(dda->hit == 0 && wall->x > 0 && wall->y > 0 && wall->x < 28 * 64 && wall->y < 28 * 64)
    {
        if (dda->side_dist.x < dda->side_dist.y)
        {
            dda->side_dist.x += dda->delta_dist.x;
            wall->x += dda->step.x;
            wall->side = 0;
        }
        else
        {
            dda->side_dist.y += dda->delta_dist.y;
            wall->y += dda->step.y;
            wall->side = 1;
        }
        //if (ray->map.map[(int)wall->y / 64][(int)wall->x / 64][0] != '0')
        if (wall->x > 0 && wall->y > 0 && wall->x < 28 * 64 && wall->y < 28 * 64)
            if ((int)wall->x % 64 == collx || (int)wall->y % 64 == colly)// || (int)wall->x % 64 == 31 || (int)wall->y % 64 == 31)// && (ray->map.map[(int)wall->y / 64][(int)wall->x / 64][0] != '#'))
             dda->hit = 1;
    }
    if (wall->side == 0)
        wall->distance = (dda->side_dist.x - dda->delta_dist.x);
    else
        wall->distance = (dda->side_dist.y - dda->delta_dist.y);
}

void     init_dda(t_ray *ray, t_wall *wall, t_dda *dda)
{
    dda->hit = 0;
    dda->delta_dist.x = absf(1 / wall->dx);
    dda->delta_dist.y = absf(1 / wall->dy);
    wall->side = 0;
    if (wall->dx == 0)
        dda->delta_dist.x = 10000.f;
    if (wall->dy == 0)
        dda->delta_dist.y = 10000.f;
    if (wall->dx > 0)
    {
        dda->step.x = -1;
        dda->side_dist.x = (ray->player.x - wall->x) * dda->delta_dist.x;
    }
    else
    {
        dda->step.x = 1;
        dda->side_dist.x = (wall->x + 1 - ray->player.x) * dda->delta_dist.x;
    }
    if (wall->dy > 0)
    {
        dda->step.y = -1;
        dda->side_dist.y = (ray->player.y - wall->y) * dda->delta_dist.y;
    }
    else
    {
        dda->step.y = 1;
        dda->side_dist.y = (wall->y + 1 - ray->player.y) * dda->delta_dist.y;
    }
}
