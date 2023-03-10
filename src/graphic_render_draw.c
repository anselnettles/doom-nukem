/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/10 15:38:51 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

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

void	draw_texture(t_ray *ray, t_minmax y, t_wall wall, int scaled_y, int wall_layer)			//FIX ME
{
	t_vectorif	texture;
	float		j;
	uint32_t	color;
	float		shade_multiplier;

	shade_multiplier = 5;
	j = 64.f / (BITS / wall.distance * ray->gfx.proj_dist);
	texture.y = 63.f;
	texture.x = get_texture_x(ray, wall);
	while (scaled_y >= y.max)
	{
		scaled_y--;
		texture.y -= j;
	}
	while (y.max > y.min && y.max >= 0)
	{
		while(texture.y < 0)
			texture.y += 63;
		if (y.max >= 0 && y.max < ray->gfx.height)
			if (wall.lock[y.max] == '0')
			{
				color = ray->gfx.texture[1].frame[0].pixels[texture.x + ((int)texture.y * 64)];	//"Clean" texture draw.
				if (wall_layer && ray->gfx.texture[13].frame[(wall_layer - 1) + ray->gfx.frame.algae].pixels[texture.x + ((int)texture.y * 64)])
					color = ray->gfx.texture[13].frame[(wall_layer - 1) + ray->gfx.frame.algae].pixels[texture.x + ((int)texture.y * 64)];
				color = fade_brightness(color, (int)((wall.distance / 500) + (j / 4)) + shade_multiplier);	//Draw shading tests.
				pixel_put(&ray->gfx, ray->x, y.max, color);
				shade_multiplier -= 0.004;
			}
		y.max--;
		texture.y -= j;
	}
}

int		draw_goal_point(t_ray *ray, t_wall *wall, int win_y, float distance)
{
	float	texture_at_distance;
	float		i;
	int			j;
	int			f;
	t_vectorif	texture;

	if (get_value(ray->map, wall->x, wall->y,3) != 'Z')
		return (0);
	texture_at_distance = 64 / distance * ray->gfx.proj_dist;		//replace 64 with sprite_height
	i = 64 / texture_at_distance;			//63 == sprite_height - 1
	j = 0;
	f = ray->gfx.frame.bottle;
	texture.x = get_texture_x(ray, *wall);
	if (texture.x > 16)
		return(0);//texture_x -= 16;
	texture.y = 62;
	while (texture.y >= 0 && win_y - j >= 0 && j <= texture_at_distance)
	{
		if (ray->gfx.texture[14].frame[f].pixels[texture.x + ((int)texture.y * 16)] && win_y - j < ray->gfx.height && win_y - j < wall->prev_y)
		{
			pixel_put(&ray->gfx, ray->x, win_y - j,
				ray->gfx.texture[14].frame[f].pixels[texture.x + ((int)texture.y * 16)]);
			wall->lock[win_y - j] = '1';
		}
		j++;
		texture.y -= i;
	}
	return (win_y - j);
}

int		draw_sprite(t_ray *ray, t_wall *wall, int win_y, float distance)
{
	float	texture_at_distance;
	float		i;
	int			j;
	int			f;
	int			texture_x;
	float		texture_y;

	if (get_value(ray->map, wall->x, wall->y,3) != '$')
		return (0);
	texture_at_distance = 64 / distance * ray->gfx.proj_dist;		//replace 64 with sprite_height
	i = 64 / texture_at_distance;			//63 == sprite_height - 1
	j = 0;
	f = ray->gfx.frame.bottle;
	texture_x = get_texture_x(ray, *wall);
	if (texture_x > 38)
		texture_x -= 38;
	texture_y =  63;
	while (texture_y >= 0 && win_y - j > 0 && j <= texture_at_distance)
	{
		if (ray->gfx.texture[8].frame[f].pixels[texture_x + ((int)texture_y * 38)] && win_y - j < ray->gfx.height && win_y - j < wall->prev_y)
		{
			pixel_put(&ray->gfx, ray->x, win_y - j,
				ray->gfx.texture[8].frame[f].pixels[texture_x + ((int)texture_y * 38)]);
			wall->lock[win_y - j] = '1';
		}
		j++;
		texture_y -= i;
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
	if ((int)roundf(wall.x / 64) >= 28 || (int)roundf(wall.y / 64) >= 20
		|| wall.y <= 0 || wall.x <= 0)
		return (0);
	if (win_y < 0 || wall.lock[win_y] != '0' || win_y >= wall.prev_y)
		return (0);
	return (1);
}

int	draw_wall_top(t_ray *ray, t_wall wall, int win_y, int wall_height)
{
	t_vector	txtr;
	float		limit;
	float		dir;

	limit = calc_limit(wall, ray);
	while (win_y > ray->gfx.height)
			win_y--;
	while (win_y >= 0)
	{
		txtr = cast_floor(ray, &wall, win_y,
				ray->player.height - (float)wall_height * 8.f);
		if (wall.distance <= 0 || wall.distance > limit)
			break ;
		if (check_boundary(wall, win_y))
			pixel_put(&ray->gfx, ray->x, win_y,
				ray->gfx.texture[1].frame[0].pixels[txtr.x + (txtr.y * 64)]);
		win_y--;
	}
	if (win_y < wall.prev_y)
		return (win_y);
	return (wall.prev_y);
}

int	get_wall_layer(int c)
{
	if (c == '\'')
		return (1);
	if (c == '"')
		return (3);
	return (0);
}

int	calc_wall_values(t_minmax *y, t_minmax *h, t_ray *ray, t_wall *wall)
{
	h->min = 64;
	if (get_value(ray->map, wall->x, wall->y, 0) != '#')
		h->min = get_value(ray->map, wall->x, wall->y, 0) - '0';
	h->max = ((BITS / 8) / wall->distance * ray->gfx.proj_dist) * h->min;
	y->max = ray->height + (((BITS) / wall->distance * ray->gfx.proj_dist) / 2);
	y->max += ((ray->player.height - ray->player.base_height)
			/ wall->distance * ray->gfx.proj_dist);
	y->min = y->max - h->max;
	return (y->max);
}

void	draw_thread(t_ray *ray, float distance, t_wall *wall)
{
	t_minmax	y;
	t_minmax	h;
	int			scaled_y_max;
	int			wall_layer;

	if (distance < 5)
		distance = 5;
	wall->distance = distance;
	scaled_y_max = calc_wall_values(&y, &h, ray, wall);
	if (y.min <= ray->gfx.height)
	{
		if (y.max > wall->prev_y || y.min > wall->prev_y)
			y.max = wall->prev_y;
		wall_layer = get_wall_layer(get_value(ray->map, wall->x, wall->y, 4));
		draw_texture(ray, y, *wall, scaled_y_max, wall_layer);
		draw_floor(ray, *wall, y.max);
	}
	draw_sprite(ray, wall, y.min, distance);
	draw_goal_point(ray, wall, y.min, distance);
	if (h.min * 8 < ray->player.height && h.min != 0)
		wall->prev_y = draw_wall_top(ray, *wall, scaled_y_max - h.max, h.min);
	if (y.min < wall->prev_y)
		wall->prev_y = y.min;
}
