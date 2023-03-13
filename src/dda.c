/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 00:24:32 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/13 17:34:28 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

float	absf(float value)
{
	if (value < 0)
		return (-value);
	return (value);
}

/*void    diagonal_1(t_ray *ray, t_wall wall, t_dda *dda)
{
	float   limit;
	
	limit = calc_limit(wall, ray);
	if (wall.side == 0)
	{
		limit -= dda->side_dist.x;
		dda->side_dist.x += limit / 2;
	}
	else
	{
		limit -= dda->side_dist.y;
		dda->side_dist.y += limit / 2;
	}
	
}

int     init_diagonal(t_ray *ray, t_wall wall, t_dda *dda, char c)
{
	if (c == '\\')
		diagonal_1(ray, wall, dda);
	if (c == '/')
		diagonal_1(ray, wall, dda);
	if (c == '<')
		diagonal_1(ray, wall, dda);
	if (c == '>')
		diagonal_1(ray, wall, dda);
	return(0);
}

int     diagonal_dda(t_ray *ray, t_wall *wall, t_dda *dda)
{
	char c;

	c =  ray->map.map[(int)wall->y / 64][(int)wall->x / 64][2];
	if (wall->side == 0)
	{
		if ((wall->dx < 0 && c == '\\') || (wall->dx < 0 && c == '>')|| (wall->dx > 0 && c == '/') || (wall->dx > 0 && c == '<'))
			return(0);
	}
	else
	{
		if ((wall->dy > 0 && c == '\\') || (wall->dy < 0 && c == '>')|| (wall->dy > 0 && c == '/') || (wall->dy < 0 && c == '<'))
			return(0);
	}
	init_diagonal(ray, *wall, dda, c);
	return(1);
}*/

float	algo_dda(t_wall *wall, t_dda *dda)
{
	int		collx;
	int		colly;

	collx = (int)roundf(31.5f - wall->dx);
	colly = (int)roundf(31.5f - wall->dy);
	dda->hit = 0;
	while (dda->hit == 0)// && wall->x > 0 && wall->y > 0 && wall->x < 28 * 64 && wall->y < 28 * 64)
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
		}//if (wall->x > 0 && wall->y > 0 && wall->x < 28 * 64 && wall->y < 28 * 64)
		if ((int)wall->x % 64 == collx || (int)wall->y % 64 == colly)
			dda->hit = 1;
	}/*if (ray->map.map[(int)roundf(wall->y / 64)][(int)roundf(wall->x / 64)][2] != '.') \n diagonal_dda(ray, wall, dda);*/
	if (wall->side == 0)
		return (dda->side_dist.x - dda->delta_dist.x);
	return (dda->side_dist.y - dda->delta_dist.y);
}

void	init_dda(t_ray *ray, t_wall *wall, t_dda *dda)
{
	dda->hit = 0;
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
