/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/02/09 15:42:43 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "drowning.h"

/*
t_txt	create_checkerboard(Uint32 color_one, Uint32 color_two)
{
	t_txt	texture;
	int		x;
	int		y;
	int		rotate;

	y = 0;
	rotate = 1;
	while(y < 64)
	{
		x= 0;
		while (x < 64)
		{
			if (x % 2 == rotate)
				texture.texture[y][x] = color_one;
			else
				texture.texture[y][x] = color_two;
			x++;
		}
		if (rotate == 1)
			rotate = 0;
		else
			rotate = 1;
		y++;
	}
	return(texture);
}

t_txt	big_checkerboard(Uint32 color_one, Uint32 color_two)
{
	t_txt	texture;
	int			x;
	int			y;

	x = 0;
	y = 0;
	while (y < 32)
	{
		x = 0;
		while (x < 64)
		{
			if (x < 32)
				texture.texture[y][x] = color_one;
			else
				texture.texture[y][x] = color_two;
			x++;
		}
		y++;
	}
	while (y < 64)
	{
		x = 0;
		while (x < 64)
		{
			if (x < 32)
				texture.texture[y][x] = color_two;
			else
				texture.texture[y][x] = color_one;
			x++;
		}
		y++;
	}
	return(texture);
}
*/
void	draw_texture(t_ray *ray, int y, int y_max, t_wall wall, int limiter)			//FIX ME
{
	int			texture_y;
	int			texture_x;
	float		i;
	int			j;

	i = (float)(y_max - y) / 64;
	j = 0;
	texture_y = 0;
	texture_x = (int)wall.x % 64;
	if (ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x + 1 )] == '0'
		|| ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x - 1 )] == '0')
		texture_x = (int)wall.y % 64;
	while (y <= y_max)
	{
		if (j >= i)
		{
			j = 0;
			texture_y += 1;
		}
		if (y >= 0 && y < ray->gfx.height  && y >= limiter)
			pixel_put(&ray->gfx, ray->x, y, ray->gfx.txt.texture_b[texture_y][texture_x]);
		y++;
		j++;
	}
}

// void	draw_texture(t_ray *ray, int y, int y_max, t_wall wall, int limiter)
// {
// 	float		texture_y;
// 	int			texture_x;
// 	float		i;

// 	texture_x = (int)wall.x % 64;
// 	texture_y = 0;
// 	i = (float)(y_max - y) / 64;
// 	if (wall.dir < PI && wall.dir > PI - 180 * DEGREES)

	
// }

void	draw_floor(t_ray *ray, t_wall wall, int win_y)
{
	int tx;
	int ty;
	float	dir;

	while (win_y < wall.prev_y && win_y < ray->gfx.height)
	{
		dir = atanf((float)(win_y - ray->height) / ray->gfx.dop);
		wall.distance = ray->player.height / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x - wall.dx * wall.distance;
		wall.y = ray->player.y - wall.dy * wall.distance;
		tx = (int)roundf(wall.y) % 64;
		ty = (int)roundf(wall.x) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y > 0)
			pixel_put(&ray->gfx, ray->x, win_y, ray->gfx.txt.texture_a[ty][tx]);
		win_y++;
	}
}

void	draw_ceiling(t_ray *ray, t_wall wall, int win_y)
{
	int tx;
	int ty;
	float	player_height;
	float	dir;

	player_height = 64 - ray->player.height;
	if (player_height < 8)
		player_height = 4;
	while (win_y >= 0)
	{
		dir = atanf((float)(win_y - ray->height) / ray->gfx.dop);
		wall.distance = 320 / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x + wall.dx * wall.distance;
		wall.y = ray->player.y + wall.dy * wall.distance;
		tx = (int)roundf(wall.x) % 128;
		ty = (int)roundf(wall.y) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y < ray->gfx.height )
			pixel_put(&ray->gfx, ray->x, win_y, ray->gfx.txt.skybox[ty][tx]);
		win_y--;
	}
}


void	draw_thread(t_ray *ray, float distance, t_wall *wall)
{
	int			y;
	int			y_max;
	int 		height;
	int			scaled_y;
	int			wall_height;

	if (distance < 1)
		distance = 1;
	height = 64;
	if (ray->map.map[(int)roundf(wall->y)][(int)roundf(wall->x)] != '#')
		height =  ray->map.map[(int)roundf(wall->y)][(int)roundf(wall->x)] - '0';
	wall_height = ((BITS / 8) / distance * ray->gfx.dop) * height;
	y_max = ray->height + ((BITS + ray->player.height - 32) / distance * (ray->gfx.dop) / 2);
	scaled_y = y_max - ((BITS + ray->player.height - 32) / distance * ray->gfx.dop);
	y = y_max - wall_height;
	if (ray->map.map[(int)roundf(wall->y)][(int)roundf(wall->x)] == '#')
		scaled_y = y;
	if (y < 0)
		y = 0;
	if (y_max > ray->gfx.height) 
		y_max = ray->gfx.height;
	if (y_max > wall->prev_y || y > wall->prev_y)
		y_max = wall->prev_y;
	if (y <= wall->prev_y || y > ray->gfx.height )
		draw_ceiling(ray, *wall, wall->prev_y);
	draw_floor(ray, *wall, y_max);
	draw_texture(ray, scaled_y, y_max, *wall, y);
	if (y < wall->prev_y)
		wall->prev_y = y;
}
