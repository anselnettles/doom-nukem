/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 00:24:32 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/14 13:49:40 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

float	absf(float value)
{
	if (value < 0)
		return (-value);
	return (value);
}

float	algo_dda(t_wall *wall, t_dda *dda)
{
	t_vector	coll;

	coll.x = (int)roundf(31.51f - wall->dx);
	coll.y = (int)roundf(31.51f - wall->dy);
	dda->hit = 0;
	while (dda->hit == 0)
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
		if ((int)wall->x % 64 == coll.x || (int)wall->y % 64 == coll.y)
			dda->hit = 1;
	}
	if (wall->side == 0)
		return (dda->side_dist.x - dda->delta_dist.x);
	return (dda->side_dist.y - dda->delta_dist.y);
}

void	init_dda(t_ray *ray, t_wall *wall, t_dda *dda)
{
	dda->delta_dist.x = absf(1 / wall->dx);
	dda->delta_dist.y = absf(1 / wall->dy);
	wall->side = 0;
	dda->step.x = 1;
	dda->step.y = 1;
	if (wall->dx == 0)
		dda->delta_dist.x = 1000000.f;
	if (wall->dy == 0)
		dda->delta_dist.y = 1000000.f;
	if (wall->dx > 0)
	{
		dda->step.x = -1;
		dda->side_dist.x = (ray->player.x - wall->x) * dda->delta_dist.x;
	}
	else
		dda->side_dist.x = (wall->x + 1 - ray->player.x) * dda->delta_dist.x;
	if (wall->dy > 0)
	{
		dda->step.y = -1;
		dda->side_dist.y = (ray->player.y - wall->y) * dda->delta_dist.y;
	}
	else
		dda->side_dist.y = (wall->y + 1 - ray->player.y) * dda->delta_dist.y;
}
