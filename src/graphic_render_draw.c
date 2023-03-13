/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/13 15:22:20 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	get_wall_layer(int c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (3);
	return (0);
}

int	get_texture_x(t_ray *ray, t_wall wall)
{
	if (wall.side == 0)
	{
		if (wall.dx < 0)
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
	texture->x = get_texture_x(ray, wall);
	texture->y = 63.f - (float)skip * j;
	return (j);
}

uint32_t	get_color(t_ray *ray, t_vectorif texture, int wall_layer, t_wall wall)
{
	uint32_t	color;
	int			i;

	i = get_value(ray->map, wall.x, wall.y, 1);
	color = ray->gfx.texture[i].frame[0].pixels[texture.x
		+ ((int)texture.y * 64)];
	if (wall_layer && ray->gfx.texture[13].frame[(wall_layer - 1)
			+ ray->gfx.frame.algae].pixels[texture.x + ((int)texture.y * 64)])
		color = ray->gfx.texture[13].frame[(wall_layer - 1)
			+ ray->gfx.frame.algae].pixels[texture.x + ((int)texture.y * 64)];
	return (color);
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
	while (y.max > y.min && y.max >= 0)
	{
		while (texture.y < 0)
			texture.y += 63;
		if (wall.lock[y.max] == '0' && y.max >= 0 && y.max < ray->gfx.height)
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
			&& win_y < ray->gfx.height && win_y < wall->prev_y)
		{
			pixel_put(&ray->gfx, ray->x, win_y,
				ray->gfx.texture[14].frame[f].pixels[txtr.x
				+ ((int)txtr.y * 16)]);
			wall->lock[win_y] = '1';
		}
		win_y--;
		txtr.y -= j;
	}
	return (win_y);
}

int	draw_sprite(t_ray *ray, t_wall *wall, int win_y, float distance)
{
	float		texture_at_distance;
	float		i;
	int			j;
	int			f;
	t_vectorif	txtr;

	if (get_value(ray->map, wall->x, wall->y, 3) != '$')
		return (0);
	texture_at_distance = 64 / distance * ray->gfx.proj_dist;//replace 64 with sprite_height
	i = 64 / texture_at_distance;//63 == sprite_height - 1
	j = 0;
	f = ray->gfx.frame.bottle;
	txtr.x = get_texture_x(ray, *wall);
	if (txtr.x > 38)
		txtr.x -= 38;
	txtr.y = 63;
	while (txtr.y >= 0 && win_y - j > 0 && j <= texture_at_distance)
	{
		if (ray->gfx.texture[8].frame[f].pixels[txtr.x + ((int)txtr.y * 38)] && win_y - j < ray->gfx.height && win_y - j < wall->prev_y)
		{
			pixel_put(&ray->gfx, ray->x, win_y - j,
				ray->gfx.texture[8].frame[f].pixels[txtr.x + ((int)txtr.y * 38)]);
			wall->lock[win_y - j] = '1';
		}
		j++;
		txtr.y -= i;
	}
	return (win_y - j);
}	

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

float	calc_limit(t_wall wall, t_ray *ray)
{
	float	limit;
	t_dda	dda;

	init_dda(ray, &wall, &dda);
	limit = algo_dda(ray, &wall, &dda);
	return (limit);
}

int	check_boundary(t_wall wall, int win_y)
{
	/*if ((int)roundf(wall.x / 64) >= 28 || (int)roundf(wall.y / 64) >= 20
		|| wall.y <= 0 || wall.x <= 0)
		return (0);*/
	if (win_y < 0 || wall.lock[win_y] != '0' || win_y >= wall.prev_y)
		return (0);
	return (1);
}

int	draw_wall_top(t_ray *ray, t_wall wall, int win_y, int wall_height)
{
	t_vector	txtr;
	int			i;
	int			win_y_limit;
	float		limit;
	float		dir;

	i  = get_value(ray->map, wall.x, wall.y, 1);
	limit = calc_limit(wall, ray) * cosf(ray->player.dir - wall.dir);
	win_y_limit = ray->height + (((BITS) / limit * ray->gfx.proj_dist) / 2);
	win_y_limit += ((ray->player.height - 32)
			/ limit * ray->gfx.proj_dist);
	win_y_limit -= ((BITS / 2) / limit * ray->gfx.proj_dist) * wall_height;
	while (win_y > ray->gfx.height)
			win_y--;
	while (win_y >= 0)
	{
		txtr = cast_floor(ray, &wall, win_y,
				ray->player.height - (float)(wall_height * 32));
		if (wall.distance <= 0 || win_y < win_y_limit || wall.distance > 100000)//wall.distance > limit)
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
	draw_sprite(ray, wall, y.min, distance);
	if (get_value(ray->map, wall->x, wall->y, 3) == 'Z')
		draw_goal_point(ray, wall, y.min, distance);
	if (h.min * 32 < ray->player.height && h.min != 0)
		wall->prev_y = draw_wall_top(ray, *wall, scaled_y_max - h.max, h.min);
	if (y.min < wall->prev_y)
		wall->prev_y = y.min;
}
