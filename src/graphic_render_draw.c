/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/02/26 16:16:05 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	get_texture_x(t_ray *ray, t_wall wall)
{
	char	c;

	return ((int) wall.x % BITS);
	c = ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][0];
	if (ray->map.map[(int)roundf(wall.y - 1) / BITS][(int)roundf(wall.x / BITS)][0] != c)
		return (BITS - (int)wall.x % BITS);
	if (ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x + 1) / BITS][0] != c)
		return (BITS - (int)wall.y % BITS);
	if (ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x - 1) / BITS][0] != c)
		return ((int)wall.y % BITS);
	return ((int)wall.x % BITS);
}

void	draw_texture(t_ray *ray, int y, int y_max, t_wall wall, float distance, int scaled_y)			//FIX ME
{
	float		texture_at_distance;
	float		texture_y;
	int			texture_x;
	float		i;
	int			j;

	texture_at_distance = BITS / distance * ray->gfx.proj_dist;
	i = 64 / texture_at_distance;
	j = 0;
	texture_y = 63;
	texture_x = get_texture_x(ray, wall);
	while (scaled_y >= y_max)
	{
		scaled_y--;
		texture_y -= i;
		if (texture_y < 0)
			texture_y = 63;
	}
	while (y_max - j > y && y_max - j > 0)
	{
		if (j > texture_at_distance || texture_y < 0)
		{
			y_max -= j;
			j = 0;
			texture_y = 63;
		}
		if (y_max - j >= 0 && y_max - j < ray->gfx.height)
		{
			pixel_put(&ray->gfx, ray->x, y_max - j,
				ray->gfx.texture[1].frame[0].pixels[texture_x + ((int)texture_y * 64)]);
		}
		j++;
		texture_y -= i;
	}
}

void	draw_floor(t_ray *ray, t_wall wall, int win_y)
{
	int		tx;
	int		ty;
	float	dir;

	while (win_y < wall.prev_y && win_y < ray->gfx.height)
	{
		dir = atanf((float)(win_y - ray->height) / ray->gfx.proj_dist);
		wall.distance = (ray->player.height) / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x - wall.dx * wall.distance;
		wall.y = ray->player.y - wall.dy * wall.distance;
		if (wall.distance < 0 || wall.distance > 10000)
			break;
		tx = (int)roundf(wall.y) % 64;
		ty = (int)roundf(wall.x) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y > 0)
			pixel_put(&ray->gfx, ray->x, win_y, ray->gfx.texture[0].frame[0].pixels[tx + (ty * 64)]);
		win_y++;
	}
}

void	draw_ceiling(t_ray *ray, t_wall wall, int win_y)
{
	int		tx;
	int		ty;
	float	player_height;
	float	dir;

	player_height = - ray->player.height;
	if (player_height < 8)
		player_height = 4;
	while (win_y >= 0)
	{
		dir = atanf((float)(win_y - ray->height) / ray->gfx.proj_dist);
		wall.distance = 512 / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x + wall.dx * wall.distance;
		wall.y = ray->player.y + wall.dy * wall.distance;
		tx = (int)roundf(wall.x) % 128;
		ty = (int)roundf(wall.y) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y < ray->gfx.height)
			pixel_put(&ray->gfx, ray->x, win_y, ray->gfx.texture[4].frame[0].pixels[tx + (ty * 128)]);
		win_y--;
	}
}

int		draw_wall_top(t_ray *ray, t_wall wall, int win_y, int wall_height, int wall_screen_height)
{
	int tx;
	int ty;
	int tmp;
	char	c;
	float	dir;

	c = ray->map.map[(int)roundf(wall.y / 64)][(int)roundf(wall.x / 64)][0];
	tmp = win_y - wall_screen_height;
	while (win_y - wall_screen_height > 0 && tmp > 0 && win_y - wall_screen_height < ray->gfx.height)
	{
		dir = atanf((float)(win_y - wall_screen_height - ray->height) / ray->gfx.proj_dist);
		wall.distance = (ray->player.height - (float)wall_height * 8.f) / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x - wall.dx * wall.distance;
		wall.y = ray->player.y - wall.dy * wall.distance;
		tx = (int)roundf(wall.y) % 64;
		ty = (int)roundf(wall.x) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (wall.distance < 0 || wall.distance > 10000)
			break;
		if ((int)roundf(wall.x / 64) < 28 && (int)roundf(wall.y / 64) < 20 && wall.y > 0 && wall.x > 0)
		{
			if (ray->map.map[(int)roundf(wall.y / 64)][(int)roundf(wall.x /64)][0] == c && tmp > 0 && tmp < wall.prev_y)
			{
				pixel_put(&ray->gfx, ray->x, tmp, ray->gfx.texture[1].frame[0].pixels[tx + (ty * 64)]);
				tmp--;
			}
		}
		/*else
			break;*/
		win_y--;
	}
	return(tmp);					
}

void	draw_thread(t_ray *ray, float distance, t_wall *wall)
{
	int		y;
	int		y_max;
	int		height;
	int		wall_height;
	int		scaled_y_max;

	if (distance < 5)
		distance = 5;
	height = 64;
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][0] != '#')
		height = ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][0] - '0';
	wall_height = ((BITS / 8) / distance * ray->gfx.proj_dist) * height;
	y_max = ray->height + ((/*BITS + */ray->player.height + ray->player.base_height) / distance * (ray->gfx.proj_dist) / 2);
	scaled_y_max = y_max;
	y = y_max - wall_height;
	if (y_max > wall->prev_y || y > wall->prev_y)
		y_max = wall->prev_y;
	if (y <= wall->prev_y || y > ray->gfx.height)
		draw_ceiling(ray, *wall, wall->prev_y);
	draw_floor(ray, *wall, y_max);
	draw_texture(ray, y, y_max, *wall, distance, scaled_y_max);
	if(height < ray->player.height && y < wall->prev_y && height != 0)
		wall->prev_y = draw_wall_top(ray, *wall, scaled_y_max, height, wall_height);
	if (y < wall->prev_y)
		wall->prev_y = y;
}
