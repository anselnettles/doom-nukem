/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/24 16:53:25 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	draw_floor(t_ray *ray, t_wall wall, int win_y)
{
	t_vector	txtr;
	uint32_t	color;
	uint32_t	*texture;

	texture = ray->gfx.texture[FLOOR].frame[0].pixels;
	while (win_y < wall.prev_y && win_y < ray->gfx.height && win_y > 0 && win_y > wall.prev_y_max)
	{
		txtr = cast_floor(ray, &wall, win_y, ray->player.height);
		if (wall.distance < 0 || wall.distance > 10000)
			break ;
		color = shader(&ray->gfx, texture[txtr.x + (txtr.y * TEXTURE_WIDTH)],
			((wall.distance) / 45));
		if (win_y < ray->gfx.height && ray->lock[win_y] == '0')
			pixel_put(&ray->gfx, ray->x, win_y, color);
		win_y++;
	}
}

int		draw_ceiling(t_ray *ray, t_wall wall, int win_y, int wall_height)
{
	t_vector	txtr;
	int			i;
	int			roof_y;
	int			win_y_limit;
	float		limit;

	i = get_value(ray->map, wall.x, wall.y, 1);
	limit = calc_limit(wall, ray) * cosf(ray->player.dir - wall.dir);
	roof_y =  ((BITS / 2) / wall.distance * ray->gfx.proj_dist) * 2;
	roof_y = win_y - roof_y;
	win_y_limit = calc_win_y(limit, ray, wall_height + 2);
	txtr.x = 0;
	/*while (win_y >= 0 && ray->player.height < (wall_height + 2) * 32)
	{
		txtr = cast_floor(ray, &wall, ray->gfx.height - win_y_limit, (float)((wall_height + 2) * 32) - ray->player.height);
		if (wall.distance <= 0 || roof_y < win_y_limit || wall.distance > 100000)
			break ;
		if (check_boundary(wall, win_y_limit, ray) && win_y_limit > wall.prev_y_max)
		{
			pixel_put(&ray->gfx, ray->x, win_y_limit, ray->gfx.texture[i].frame[0].pixels[txtr.x + (txtr.y * 64)]);
			ray->lock[win_y_limit] = '1';
		}
		win_y_limit--;
		//roof_y -= 2;
	}*/
	return(roof_y);
}

int	draw_wall_top(t_ray *ray, t_wall wall, int win_y, int wall_height)
{
	t_vector	txtr;
	int			i;
	int			win_y_limit;
	float		limit;
	uint32_t	color;
	uint32_t	*texture;

	i = get_value(ray->map, wall.x, wall.y, 1);
	texture = ray->gfx.texture[i].frame[0].pixels;
	limit = calc_limit(wall, ray) * cosf(ray->player.dir - wall.dir);
	win_y_limit = calc_win_y(limit, ray, wall_height);
	while (win_y > ray->gfx.height)
			win_y--;
	while (win_y >= 0)
	{
		txtr = cast_floor(ray, &wall, win_y,
				ray->player.height - (float)(wall_height * 32));
		if (wall.distance <= 0 || win_y < win_y_limit || wall.distance > 100000)
			break ;
		if (check_boundary(wall, win_y, ray) && win_y > wall.prev_y_max)
		{
			if (ray->gfx.lantern == LANTERN_OFF)
				color = shader(&ray->gfx, texture[txtr.x + (txtr.y * TEXTURE_WIDTH)], ((wall.distance) / 45));
			else
			{
				if (wall.distance >= 400)
					color = shader(&ray->gfx, texture[txtr.x + (txtr.y * TEXTURE_WIDTH)], ((wall.distance) / 400));
				else
					color = shader(&ray->gfx, texture[txtr.x + (txtr.y * TEXTURE_WIDTH)], 1);
			}
			pixel_put(&ray->gfx, ray->x, win_y, color);
		}
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
	t_minmax 	tmp;
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
	if (get_value(ray->map, wall->x, wall->y, 4) == 'R')
	{
		tmp.max = draw_ceiling(ray, *wall, scaled_y_max - h.max, h.min);
		tmp.min = 0;
		draw_texture(ray, tmp, *wall, tmp.max);
		if (tmp.max > wall->prev_y_max)
			wall->prev_y_max = tmp.max;
	}
	if (y.min < wall->prev_y)
		wall->prev_y = y.min;
}
