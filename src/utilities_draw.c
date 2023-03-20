/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:16:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/14 20:00:41 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

t_vector	cast_floor(t_ray *ray, t_wall *wall, int win_y, float height)
{
	float		dir;
	t_vector	texture;

	dir = atanf((float)(win_y - ray->height) / ray->gfx.proj_dist);
	wall->distance = (height) / dir;
	wall->distance /= cosf(ray->player.dir - wall->dir);
	wall->x = ray->player.x - wall->dx * wall->distance;
	wall->y = ray->player.y - wall->dy * wall->distance;
	texture.x = (int)roundf(wall->y) % 64;
	texture.y = (int)roundf(wall->x) % 64;
	return (texture);
}

float	calc_limit(t_wall wall, t_ray *ray)
{
	float	limit;
	t_dda	dda;

	init_dda(ray, &wall, &dda);
	limit = algo_dda(&wall, &dda);
	return (limit);
}

int	calc_win_y(float limit, t_ray *ray, int wall_height)
{
	int	win_y_limit;

	win_y_limit = ray->height + (((BITS) / limit * ray->gfx.proj_dist) / 2);
	win_y_limit += ((ray->player.height - 32)
			/ limit * ray->gfx.proj_dist);
	win_y_limit -= ((BITS / 2) / limit * ray->gfx.proj_dist) * wall_height;
	return (win_y_limit);
}

int	check_boundary(t_wall wall, int win_y, t_ray *ray)
{
	if (win_y < 0 || ray->lock[win_y] != '0' || win_y >= wall.prev_y)
		return (0);
	return (1);
}

int	draw_player_tile(t_ray *ray, t_wall wall)
{
	t_vector	txtr;
	int			i;
	int			win_y_limit;
	float		limit;
	int			wall_height;

	if (get_value(ray->map, wall.x, wall.y, 0)
		!= get_value(ray->map, ray->player.x, ray->player.y, 0))
		return (wall.prev_y);
	wall_height = (get_value(ray->map, ray->player.x, ray->player.y, 0) - '0');
	i = get_value (ray->map, wall.x, wall.y, 1);
	limit = calc_limit(wall, ray) * cosf(ray->player.dir - wall.dir);
	win_y_limit = calc_win_y(limit, ray, wall_height);
	while (wall.prev_y >= win_y_limit && wall.prev_y > 0)
	{
		txtr = cast_floor(ray, &wall, wall.prev_y, ray->player.height
				- (float)(wall_height * 32.f));
		if (wall.distance <= 0 || wall.distance > 100000)
			break ;
		pixel_put(&ray->gfx, ray->x, wall.prev_y,
			ray->gfx.texture[i].frame[0].pixels[txtr.x + (txtr.y * 64)]);
		wall.prev_y--;
	}
	return (wall.prev_y);
}
