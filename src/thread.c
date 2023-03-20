/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:13:05 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/15 14:02:55 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	init_thread(t_ray *ray, t_drown *data, int i)
{
	ray->count = 0;
	if (i == 0)
	{
		ray->x = -1;
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
	ray->nearest = 6000;
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
		rc = pthread_create(&threads[i], NULL, ft_raycast, &ray[i]);
		i++;
	}
	i = 0;
	while (i < THREAD)
	{
		rc = pthread_join(threads[i], NULL);
		i++;
	}
	data->gfx.nearest = ray[0].nearest;
	if (ray[1].nearest < ray[0].nearest)
		data->gfx.nearest = ray[1].nearest;
}
