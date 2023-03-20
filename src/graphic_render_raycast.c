/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:49:19 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/16 10:59:37 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	ft_bzero_char(void *dst, size_t n)
{
	char	*s;

	s = dst;
	while (n)
	{
		*s = '0';
		s++;
		n--;
	}
}

void	init_new_wall(t_ray *ray, t_wall *wall)
{
	wall->distance = 0;
	if (wall->dir > 2 * PI)
		wall->dir -= 2 * PI;
	if (wall->dir < 0)
		wall->dir += 2 * PI;
	wall->dx = cosf(wall->dir);
	wall->dy = sinf(wall->dir);
	wall->x = ray->player.x + 1;
	if (wall->dx > 0)
		wall->x -= 2;
	wall->y = ray->player.y + 1;
	if (wall->dy > 0)
		wall->y -= 2;
	ray->x++;
	ray->count++;
	ft_bzero_char(ray->lock, ray->gfx.height);
	wall->prev_y = ray->gfx.height;
	wall->prev_y_max = 0;
	wall->prev_y = draw_player_tile(ray, *wall);
}

float	check_nearest(t_ray *ray, t_wall wall)
{
	if (ray->x > ray->gfx.width / 3)
		return (0);
	if (wall.distance < ray->nearest && (get_value(ray->map, wall.x, wall.y, 0)
			- '0') * 8 > ray->player.altitude)
		return (wall.distance);
	return (ray->nearest);
}

void	init_wall_lock(t_ray *ray)
{
	ray->lock = (char *)malloc(sizeof(char) * ray->gfx.height + 1);
	if (ray->lock == NULL)
		exit(-1);
	ray->lock[ray->gfx.height + 1] = '\0';
}

void	*ft_raycast(void *args)
{
	t_ray		*ray;
	t_wall		wall;
	t_dda		dda;

	ray = args;
	wall.dir = ray->dir;
	init_wall_lock(ray);
	while (ray->count < (ray->gfx.width / 6))
	{
		init_new_wall(ray, &wall);
		if (get_value(ray->map, wall.x, wall.y, 0)
			!= get_value(ray->map, ray->player.x, ray->player.y, 0))
			draw_thread(ray, 5.f, &wall);
		while (get_value(ray->map, wall.x, wall.y, 0) != '#' && wall.prev_y)
		{
			init_dda(ray, &wall, &dda);
			wall.distance = algo_dda(&wall, &dda)
				* cosf(ray->player.dir - wall.dir);
			ray->nearest = check_nearest(ray, wall);
			draw_thread(ray, wall.distance, &wall);
		}
		wall.dir += (60 * DEGREES) / ray->gfx.width;
	}
	free(wall.lock);
	return (NULL);
}
