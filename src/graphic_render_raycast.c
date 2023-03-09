/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:49:19 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/09 15:34:45 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	ft_bzero2(void *dst, size_t n)
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
	if (wall->dir > 2 * PI)
		wall->dir -= 2 * PI;
	if (wall->dir < 0)
		wall->dir += 2 * PI;
	wall->dx = cosf(wall->dir);
	wall->dy = sinf(wall->dir);
	wall->x = ray->player.x;
	wall->y = ray->player.y;
	wall->prev_y = ray->gfx.height;
	ft_bzero2(wall->lock, ray->gfx.height);
}

void	*ft_raycast_thread(void *args)
{
	t_ray		*ray;
	t_wall		wall;
	t_dda		dda;

	ray = args;
	wall.dir = ray->dir;
	wall.lock = (char *)malloc(sizeof(char) * ray->gfx.height + 1);
	if (wall.lock == NULL)
		exit(-1);
	wall.lock[ray->gfx.height + 1] = '\0';
	while (ray->count < (ray->gfx.width / 6))
	{
		init_new_wall(ray, &wall);
		while (get_value(ray->map, wall.x, wall.y, 0) != '#' && wall.prev_y)
		{
			init_dda(ray, &wall, &dda);//wall.distance = algo_dda(ray, &wall, &dda) * cosf(ray->player.dir - wall.dir);
			draw_thread(ray, algo_dda(ray, &wall, &dda)
				* cosf(ray->player.dir - wall.dir), &wall);
		}
		wall.dir += (60 * DEGREES) / ray->gfx.width;
		ray->x++;
		ray->count++;
	}
	return (NULL);
}

void	init_thread(t_ray *ray, t_drown *data, int i)
{
	ray->count = 0;
	if (i == 0)
	{
		ray->x = 0;
		ray->dir = (data->player.dir - 30 * DEGREES);
	}
	if (i != 0)
	{
		ray->x = i * (data->gfx.width / 6);
		ray->dir = (data->player.dir - 30 * DEGREES)
			+ (i * (data->gfx.width / 6) * (60 * DEGREES / data->gfx.width));
	}
	ray->height = data->gfx.centre;
	ray->gfx = data->gfx;
	ray->player = data->player;
	ray->map = data->map;
}

void	render_thread(t_drown *data)
{
	pthread_t	threads[THREAD];
	t_ray		ray[THREAD];
	int			i;
	int			rc;

	i = 0;
	while (i < THREAD)
	{
		init_thread(&ray[i], data, i);
		rc = pthread_create(&threads[i], NULL, ft_raycast_thread, &ray[i]);
		i++;
	}
	i = 0;
	while (i < THREAD)
	{
		rc = pthread_join(threads[i], NULL);
		i++;
	}
}
