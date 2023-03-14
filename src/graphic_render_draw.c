/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/14 14:31:44 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	draw_floor(t_ray *ray, t_wall wall, int win_y)
{
	t_vector	txtr;
	float		dir;
	uint32_t	color;
	int			shade_multiplier;

	shade_multiplier = 3;
	while (win_y < wall.prev_y && win_y < ray->gfx.height && win_y > 0)
	{
		txtr = cast_floor(ray, &wall, win_y, ray->player.height);
		if (wall.distance < 0 || wall.distance > 10000)
			break ;
		color = ray->gfx.texture[0].frame[0].pixels[txtr.x + (txtr.y * 64)];
		color = fade_brightness(ray->gfx.texture[0].frame[0].pixels[txtr.x
				+ (txtr.y * 64)], wall.distance / 100 * shade_multiplier);
		if (win_y < ray->gfx.height && wall.lock[win_y] == '0')
			pixel_put(&ray->gfx, ray->x, win_y, color);
		shade_multiplier += 0.2;
		win_y++;
	}
}

void	draw_ceiling(t_ray *ray, t_wall wall, int win_y)
{
	t_vector	txtr;
	float		dir;

	while (win_y >= 0)
	{
		dir = atanf((float)(win_y - ray->height) / ray->gfx.proj_dist);
		wall.distance = 512 / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x + wall.dx * wall.distance;
		wall.y = ray->player.y + wall.dy * wall.distance;
		txtr.x = (int)roundf(wall.x) % 128;
		txtr.y = (int)roundf(wall.y) % 64;
		if (win_y < ray->gfx.height && wall.lock[win_y] == '0')
			pixel_put(&ray->gfx, ray->x, win_y,
				ray->gfx.texture[4].frame[0].pixels[txtr.x + (txtr.y * 128)]);
		win_y--;
	}
}

int	draw_wall_top(t_ray *ray, t_wall wall, int win_y, int wall_height)
{
	t_vector	txtr;
	int			i;
	int			win_y_limit;
	float		limit;
	float		dir;

	i = get_value(ray->map, wall.x, wall.y, 1);
	limit = calc_limit(wall, ray) * cosf(ray->player.dir - wall.dir);
	win_y_limit = calc_win_y(limit, ray, wall, wall_height);
	while (win_y > ray->gfx.height)
			win_y--;
	while (win_y >= 0)
	{
		txtr = cast_floor(ray, &wall, win_y,
				ray->player.height - (float)(wall_height * 32));
		if (wall.distance <= 0 || win_y < win_y_limit || wall.distance > 100000)
			break ;
		if (check_boundary(wall, win_y))
			pixel_put(&ray->gfx, ray->x, win_y,
				ray->gfx.texture[i].frame[0].pixels[txtr.x + (txtr.y * 64)]);
		win_y--;
	}
	if (win_y < wall.prev_y)
		return (win_y_limit);
	return (wall.prev_y);
}

int	calc_wall_values(t_minmax *y, t_minmax *h, t_ray *ray, t_wall *wall)
{
	h->min = 26;
	if (get_value(ray->map, wall->x, wall->y, 0) != '#')
		h->min = get_value(ray->map, wall->x, wall->y, 0) - '0';
	h->max = ((BITS / 2) / wall->distance * ray->gfx.proj_dist) * h->min;
	y->max = ray->height + (((BITS) / wall->distance * ray->gfx.proj_dist) / 2);
	y->max += ((ray->player.height - 32)
			/ wall->distance * ray->gfx.proj_dist);
	y->min = y->max - h->max;
	return (y->max);
}

void	draw_thread(t_ray *ray, float distance, t_wall *wall)
{
	t_minmax	y;
	t_minmax	h;
	int			scaled_y_max;

	if (distance < 5)
		distance = 5;
	wall->distance = distance;
	scaled_y_max = calc_wall_values(&y, &h, ray, wall);
	if (y.min <= ray->gfx.height)
	{
		if (y.max > wall->prev_y || y.min > wall->prev_y)
			y.max = wall->prev_y;
		draw_texture(ray, y, *wall, scaled_y_max);
		draw_floor(ray, *wall, y.max);
	}
	if (get_value(ray->map, wall->x, wall->y, 3) == '$')
		draw_sprite(ray, wall, y.min, distance);
	if (get_value(ray->map, wall->x, wall->y, 3) == 'Z')
		draw_goal_point(ray, wall, y.min, distance);
	if (h.min * 32 < ray->player.height && h.min != 0)
		wall->prev_y = draw_wall_top(ray, *wall, scaled_y_max - h.max, h.min);
	if (y.min < wall->prev_y)
		wall->prev_y = y.min;
}
