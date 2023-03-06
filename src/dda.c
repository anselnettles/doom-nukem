/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 00:24:32 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/06 14:33:30 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

float   absf(float value)
{
    if (value < 0)
        return (-value);
    return(value);
}

t_vectorf    inc_wall(t_wall *wall)
{
    t_vectorf   modulo;

    modulo.x = 0;
    modulo.y = 0;
    while ((int)(wall->x + modulo.x) % 64 != 0)
        modulo.x++;
    while ((int)(wall->y + modulo.y) % 64 != 0)
        modulo.y++;
    if (wall->dx > 0)
        modulo.x = BITS - modulo.x;
    if (wall->dy > 0)
        modulo.y = BITS - modulo.y;
    return(modulo);
}

void    print_dda(t_dda *dda)
{
    printf("delta_dist x & y = %f & %f\n", dda->delta_dist.x, dda->delta_dist.y);
    printf("step x & y = %f & %f\n", dda->step.x, dda->step.y);
    printf("side_dist x & y = %f & %f\n", dda->side_dist.x, dda->side_dist.y);
    exit(-1);
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
    //if(ray->x == 132)
      //  print_dda(dda);
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
    //printf("wall.x ==%f, wall.y == %f\n", wall->x, wall->y);
    if (wall->side == 0)
        wall->distance = (dda->side_dist.x - dda->delta_dist.x);
    else
        wall->distance = (dda->side_dist.y - dda->delta_dist.y);
}

void     init_dda(t_ray *ray, t_wall *wall, t_dda *dda)
{
    dda->hit = 0;
    dda->delta_dist.x = sqrtf(1 + (wall->dy * wall->dy) / (wall->dx * wall->dx));
    dda->delta_dist.y = sqrtf(1 + (wall->dx * wall->dx) / (wall->dy * wall->dy));
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
        //dda->side_dist.x = (wall->x + 1 - ray->player.x) * dda->delta_dist.x;
    }
    else
    {
        dda->step.x = 1;
        dda->side_dist.x = (wall->x + 1 - ray->player.x) * dda->delta_dist.x;
        //dda->side_dist.x = (ray->player.x - wall->x) * dda->delta_dist.x;
    }
    if (wall->dy > 0)
    {
        dda->step.y = -1;
        dda->side_dist.y = (ray->player.y - wall->y) * dda->delta_dist.y;
        //dda->side_dist.y = (wall->y + 1 - ray->player.y) * dda->delta_dist.y;
    }
    else
    {
        dda->step.y = 1;
        dda->side_dist.y = (wall->y + 1 - ray->player.y) * dda->delta_dist.y;
        //dda->side_dist.y = (ray->player.y - wall->y) * dda->delta_dist.y;
    }
    /*
    while(dda->hit == 0)
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
        if ((int)wall->x % 64 == 0 || (int)wall->y % 64 == 0)// && (ray->map.map[(int)wall->y / 64][(int)wall->x / 64][0] != '#'))
            dda->hit = 1;
    }
    //printf("wall.x ==%f, wall.y == %f\n", wall->x, wall->y);
    if (wall->side == 0)
        wall->distance = (dda->side_dist.x - dda->delta_dist.x);
    else
        wall->distance = (dda->side_dist.y - dda->delta_dist.y);*/
    //if (ray->player.dir == wall->dir)
        //printf("wall.distance = %f\n", wall->distance);
    //wall->distance -= sqrt(save.x * save.x + save.y * save.y);
    //wall->x = ray->player.x + wall->dx * wall->distance;
    //wall->y = ray->player.y + wall->dy * wall->distance;

}
/*
int     dda_algo(t_ray *ray, t_wall *wall)
{
    
}*/