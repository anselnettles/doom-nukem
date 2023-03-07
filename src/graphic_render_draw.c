/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_draw.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/03/07 16:36:15 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int		get_texture_x(t_ray *ray, t_wall wall)
{
	if (wall.side == 0)
	{
		if (wall.dx < 0)
			return(BITS - (int)wall.y % BITS);
		return ((int)wall.y % BITS);
	}
	else
	{
		if (wall.dy < 0)// && ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][2] != '.')
			return(BITS - (int)wall.x % BITS);
		return((int)wall.x % BITS);
	}
}

void	draw_texture(t_ray *ray, int y, int y_max, t_wall wall, float distance, int scaled_y, int wall_layer)			//FIX ME
{
	float		texture_at_distance;
	float		texture_y;
	int			texture_x;
	float		i;
	int			j;
	uint32_t	color;
	float		shade_multiplier = 5;

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
			if (wall.lock[y_max - j] == '0')
			{
				color = ray->gfx.texture[1].frame[0].pixels[texture_x + ((int)texture_y * 64)];	//"Clean" texture draw.
				if (wall_layer && ray->gfx.texture[13].frame[(wall_layer - 1) + ray->gfx.frame.algae].pixels[texture_x + ((int)texture_y * 64)])
					color = ray->gfx.texture[13].frame[(wall_layer - 1) + ray->gfx.frame.algae].pixels[texture_x + ((int)texture_y * 64)];
				color = fade_brightness(color, (int)((distance / 500) + (i / 4)) + shade_multiplier);	//Draw shading tests.
				pixel_put(&ray->gfx, ray->x, y_max - j, color);
				shade_multiplier -= 0.004;
			}
		j++;
		texture_y -= i;
	}
}

int		draw_goal_point(t_ray *ray, t_wall *wall, int win_y, float distance)
{
	float	texture_at_distance;
	float		i;
	int			j;
	int			f;
	int			texture_x;
	float		texture_y;

	texture_at_distance = 64 / distance * ray->gfx.proj_dist;		//replace 64 with sprite_height
	i = 64 / texture_at_distance;			//63 == sprite_height - 1
	j = 0;
	f = ray->gfx.frame.bottle;
	//win_y -= (int)texture_at_distance / 5;
	texture_x = get_texture_x(ray, *wall);
	if (texture_x > 16)
		texture_x -= 16;
	texture_y =  63;
	while (texture_y >= 0 && win_y - j > 0 && j <= texture_at_distance)
	{
		if (ray->gfx.texture[14].frame[f].pixels[texture_x + ((int)texture_y * 16)] && win_y - j < ray->gfx.height && win_y - j < wall->prev_y)
		{
			pixel_put(&ray->gfx, ray->x, win_y - j,
				ray->gfx.texture[14].frame[f].pixels[texture_x + ((int)texture_y * 16)]);
			wall->lock[win_y - j] = '1';
		}
		j++;
		texture_y -= i;
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

	texture_at_distance = 64 / distance * ray->gfx.proj_dist;		//replace 64 with sprite_height
	i = 64 / texture_at_distance;			//63 == sprite_height - 1
	j = 0;
	f = ray->gfx.frame.bottle;
	//win_y -= (int)texture_at_distance / 5;
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

void	draw_floor(t_ray *ray, t_wall wall, int win_y)
{
	t_vector	texture;
	float		dir;
	uint32_t	color;
	int			shade_multiplier = 3;

	while (win_y < wall.prev_y && win_y < ray->gfx.height)
	{
		dir = atanf((float)(win_y - ray->height) / ray->gfx.proj_dist);
		wall.distance = (ray->player.height) / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x - wall.dx * wall.distance;
		wall.y = ray->player.y - wall.dy * wall.distance;
		if (wall.distance < 0 || wall.distance > 10000)
			break;
		texture.x = (int)roundf(wall.y) % 64;
		texture.y = (int)roundf(wall.x) % 64;
		if (win_y > 0)
		{
			color = ray->gfx.texture[0].frame[0].pixels[texture.x + (texture.y * 64)];	//"Clean" texture draw.
			color = fade_brightness(ray->gfx.texture[0].frame[0].pixels[texture.x + (texture.y * 64)], wall.distance / 100 * shade_multiplier);	//Draw shading tests.
			if (win_y < ray->gfx.height && wall.lock[win_y] == '0')
				pixel_put(&ray->gfx, ray->x, win_y, color);
			shade_multiplier += 0.2;
		}
		win_y++;
	}
}

void	draw_ceiling(t_ray *ray, t_wall wall, int win_y)
{
	t_vector	texture;
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
		texture.x = (int)roundf(wall.x) % 128;
		texture.y = (int)roundf(wall.y) % 64;
		if (win_y < ray->gfx.height && wall.lock[win_y] == '0')
			pixel_put(&ray->gfx, ray->x, win_y, ray->gfx.texture[4].frame[0].pixels[texture.x + (texture.y * 128)]);
		win_y--;
	}
}

float	calc_limit(t_wall wall, t_ray *ray)
{
	float	limit;
	t_dda dda;

	init_dda(ray, &wall, &dda);
	limit = algo_dda(ray, &wall, &dda);
	return(limit);
}

int		draw_wall_top(t_ray *ray, t_wall wall, int win_y, int wall_height)
{
	t_vector texture;
	float		limit;
	float	dir;

	limit = calc_limit(wall, ray);
	while (win_y > ray->gfx.height)
			win_y--;
	while (win_y > 0)
	{
		dir = atanf((float)(win_y - ray->height) / ray->gfx.proj_dist);
		wall.distance = (ray->player.height - (float)wall_height * 8.f) / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x - wall.dx * wall.distance;
		wall.y = ray->player.y - wall.dy * wall.distance;
		texture.x = (int)roundf(wall.y) % 64;
		texture.y = (int)roundf(wall.x) % 64;
		if (wall.distance <= 0 || wall.distance > limit)
			break;
		if ((int)roundf(wall.x / 64) < 28 && (int)roundf(wall.y / 64) < 20 && wall.y > 0
			&& wall.x > 0 && win_y > 0 && wall.lock[win_y] == '0' && win_y < wall.prev_y)
			pixel_put(&ray->gfx, ray->x, win_y, ray->gfx.texture[1].frame[0].pixels[texture.x + (texture.y * 64)]);
		win_y--;
	}
	if (win_y < wall.prev_y)
		return(win_y);
	return(wall.prev_y);
}

void	draw_thread(t_ray *ray, float distance, t_wall *wall)
{
	int		y;
	int		y_max;
	int		height;
	int		wall_height;
	int		scaled_y_max;
	int		wall_layer;

	if (distance < 5)
		distance = 5;
	height = 64;
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][0] != '#')
		height = ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][0] - '0';
	wall_height = ((BITS / 8) / distance * ray->gfx.proj_dist) * height;
	y_max = ray->height + (((BITS) / distance * ray->gfx.proj_dist) / 2);
	y_max += ((ray->player.height - ray->player.base_height) / distance * ray->gfx.proj_dist);
	scaled_y_max = y_max;
	y = y_max - wall_height;
	if (y <= ray->gfx.height)
	{
	if (y_max > wall->prev_y || y > wall->prev_y)
		y_max = wall->prev_y;
	/*if (y <= wall->prev_y || y > ray->gfx.height)
		draw_ceiling(ray, *wall, wall->prev_y);*/
	draw_floor(ray, *wall, y_max);
	wall_layer = 0;
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][4] == '\'')
		wall_layer = 1;
	else if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][4] == '"')
		wall_layer = 3;
	draw_texture(ray, y, y_max, *wall, distance, scaled_y_max, wall_layer);
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][3] == '$')
		draw_sprite(ray, wall, y, distance);
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][3] == 'Z')
		draw_goal_point(ray, wall, y, distance);
	/*if (height * 8 < ray->player.height && height != 0)
		wall->prev_y = draw_wall_top(ray, *wall, scaled_y_max, height, wall_height);
	if (y < wall->prev_y)
		wall->prev_y = y;*/
	}
	if (height * 8 < ray->player.height && height != 0)
		wall->prev_y = draw_wall_top(ray, *wall, scaled_y_max - wall_height, height);
	if (y < wall->prev_y)
		wall->prev_y = y;
//	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][3] == 'I')
//		draw_sprite(ray, wall, y, distance);
}
