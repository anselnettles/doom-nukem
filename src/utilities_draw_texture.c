/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_draw_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 14:24:34 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/16 13:02:08 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	get_texture_x(t_wall wall)
{
	if (wall.side == 0)
	{
		if (wall.dx > 0)
			return (BITS - (int)wall.y % BITS);
		return ((int)wall.y % BITS);
	}
	else
	{
		if (wall.dy < 0)
			return (BITS - (int)wall.x % BITS);
		return ((int)wall.x % BITS);
	}
}

float	init_texture(t_ray *ray, t_wall wall, t_vectorif *texture, int skip)
{
	float	j;

	j = 64.f / (BITS / wall.distance * ray->gfx.proj_dist);
	texture->x = get_texture_x(wall);
	texture->y = 63.f - (float)skip * j;
	return (j);
}

void	draw_texture(t_ray *ray, t_minmax y, t_wall wall, int scaled_y)
{
	t_vectorif	texture;
	float		j;
	uint32_t	color;
	float		shade_multiplier;
	int			wall_layer;

	wall_layer = get_wall_layer(get_value(ray->map, wall.x, wall.y, 4));
	shade_multiplier = 5;
	j = init_texture(ray, wall, &texture, scaled_y - y.max);
	while (y.max > y.min && y.max >= 0 && y.max >= wall.prev_y_max)
	{
		while (texture.y < 0)
			texture.y += 63;
		if (ray->lock[y.max] == '0' && y.max >= 0 && y.max < ray->gfx.height && y.max > wall.prev_y_max)
		{
			color = get_color(ray, texture, wall_layer, wall);
			color = fade_brightness(color, (int)((wall.distance
							/ 500) + (j / 4)) + shade_multiplier);
			pixel_put(&ray->gfx, ray->x, y.max, color);
			shade_multiplier -= 0.004;
		}
		y.max--;
		texture.y -= j;
	}
}

int	draw_goal_point(t_ray *ray, t_wall *wall, int win_y, float distance)
{
	float		texture_at_distance;
	float		j;
	int			f;
	t_vectorif	txtr;

	texture_at_distance = 64 / distance * ray->gfx.proj_dist;
	j = init_texture(ray, *wall, &txtr, 0);
	f = ray->gfx.frame.bottle;
	while (win_y >= 0 && txtr.x < 16)
	{
		while (txtr.y < 0)
			txtr.y += 64;
		if (ray->gfx.texture[14].frame[f].pixels[txtr.x + ((int)txtr.y * 16)]
			&& win_y < ray->gfx.height && win_y < wall->prev_y && win_y >= wall->prev_y_max)
		{
			pixel_put(&ray->gfx, ray->x, win_y,
				ray->gfx.texture[14].frame[f].pixels[txtr.x
				+ ((int)txtr.y * 16)]);
			ray->lock[win_y] = '1';
		}
		win_y--;
		txtr.y -= j;
	}
	return (win_y);
}

int	draw_sprite(t_ray *ray, t_wall *wall, int win_y, float distance)
{
	float		texture_at_distance;
	float		j;
	int			f;
	t_vectorif	txtr;

	texture_at_distance = 64 / distance * ray->gfx.proj_dist;
	j = init_texture(ray, *wall, &txtr, 0);
	txtr.x += 19;
	if (txtr.x > 63)
		txtr.x -= 64;
	f = ray->gfx.frame.bottle;
	while (win_y >= 0 && txtr.x < 38 && txtr.y > 0)
	{
		if (ray->gfx.texture[8].frame[f].pixels[txtr.x + ((int)txtr.y * 38)]
			&& win_y < ray->gfx.height && win_y < wall->prev_y && win_y >= wall->prev_y_max)
		{
			pixel_put(&ray->gfx, ray->x, win_y,
				ray->gfx.texture[8].frame[f].pixels[txtr.x
				+ ((int)txtr.y * 38)]);
			ray->lock[win_y] = '1';
		}
		win_y--;
		txtr.y -= j;
	}
	return (win_y);
}
