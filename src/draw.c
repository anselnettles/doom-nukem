/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/02/08 13:03:07 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"
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

void	draw_texture(t_ray *ray, int y, int y_max, t_wall wall, SDL_Surface *screen, int limiter)
{
	t_txt	texture;
	int			texture_y;
	int			texture_x;
	float		i;
	int			j;

	texture = create_checkerboard(SDL_MapRGB(screen->format, 0xF7, 0xCE, 0x00), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	i = (float)(y_max - y) / 64;
	j = 0;
	texture_y = 0;
	texture_x = (int)wall.x % 64;
	if (ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x + 1 )] == '0'
		|| ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x - 1 )] == '0')
		texture_x = (int)wall.y % 64;
	while (y <= y_max && texture_y < 64)
	{
		if (j >= i)
		{
			j = 0;
			texture_y += 1;
		}
		if (y >= 0 && y < ray->gfx.height  && y >= limiter)
			pixel_put(&ray->gfx, ray->x, y, texture.texture[texture_y][texture_x]);
		y++;
		j++;
	}
}

void	draw_floor(t_ray *ray, t_wall wall, int win_y, SDL_Surface *screen)
{
	t_txt texture;
	int tx;
	int ty;
	float	dir;

	texture = big_checkerboard(SDL_MapRGB(screen->format, 0x00, 0x00, 0x00), SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
	while (win_y < wall.prev_y && win_y < ray->gfx.height)
	{
		dir = atanf((float)(win_y - (ray->gfx.height / 2) - ray->height) / (float)738);
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
			pixel_put(&ray->gfx, ray->x, win_y, texture.texture[ty][tx]);
		win_y++;
	}
}

void	draw_ceiling(t_ray *ray, t_wall wall, int win_y, SDL_Surface *screen)
{
	t_txt texture;
	int tx;
	int ty;
	float	player_height;
	float	dir;

	player_height = 64 - ray->player.height;
	if (player_height < 8)
		player_height = 4;
	texture = big_checkerboard(SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	while (win_y >= 0)
	{
		dir = atanf((float)(win_y - (ray->gfx.height / 2) - ray->height) / (float)738);
		wall.distance = player_height / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x + wall.dx * wall.distance;
		wall.y = ray->player.y + wall.dy * wall.distance;
		tx = (int)roundf(wall.y) % 64;
		ty = (int)roundf(wall.x) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y < ray->gfx.height )
			pixel_put(&ray->gfx, ray->x, win_y, texture.texture[ty][tx]);
		win_y--;
	}
}
/*
void	draw_wall_top(t_ray *ray, t_wall wall, int win_y, SDL_Surface *screen)			//IN PROGRESS
{
	t_texture	texture;
	float	x;
	float	y;
	float	dir;
	int tx;
	int ty;
	int height;

	texture = create_checkerboard(SDL_MapRGB(screen->format, 0xF7, 0xCE, 0x00), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	x = wall.x;
	y = wall.y;
	height = 8 * ray->map.map[(int)roundf(y)][(int)roundf(x)] - '0';
	while(ray->map.map[(int)roundf(y)][(int)roundf(x)] != '0'&& y > 0 && y < HEIGHT)
	{
		dir = atanf((float)(win_y - (HEIGHT / 2) - ray->height) / (float)700);
		wall.distance = (float)32 / dir;
		wall.distance /= cosf(ray->player.dir - wall.dir);
		wall.x = ray->player.x + wall.dx * wall.distance;
		wall.y = ray->player.y + wall.dy * wall.distance;
		tx = (int)roundf(wall.y) % 64;
		ty = (int)roundf(wall.x) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y < HEIGHT)
			pixel_put(screen, ray->x, win_y, texture.texture[ty][tx]);
		win_y--;
		
		// height = 8 * ray->map.map[(int)roundf(y)][(int)roundf(x)] - '0';
		// dir = atanf((float)((win_y + (height * (HEIGHT / 64))) - (HEIGHT / 2) - ray->height) /  (float)700);
		// wall.distance = ((float)32 - (float)height) / dir;
		// wall.distance /= cosf(ray->player.dir - wall.dir);
		// x = ray->player.x + wall.dx * wall.distance;
		// y = ray->player.y + wall.dy * wall.distance;
		// tx = (int)roundf(y) % 64;
		// ty = (int)roundf(x) % 64;
		// if (tx < 0)
		// 	tx *= -1;
		// if (ty < 0)
		// 	ty *= -1;
		// if (win_y > 0)
		// 	pixel_put(screen, ray->x, win_y, texture.texture[ty][tx]);
		// win_y--;
	}
}
*/
void	draw_thread(t_ray *ray, float distance, t_wall *wall)
{
	SDL_Surface *screen;
	int			y;
	int			y_max;
	int 		height;
	int			scaled_y;

	if (!(screen = SDL_GetWindowSurface(ray->gfx.window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	if (distance < 1)
		distance = 1;
	height = 8;
	if (ray->map.map[(int)roundf(wall->y)][(int)roundf(wall->x)] != '#')
		height =  ray->map.map[(int)roundf(wall->y)][(int)roundf(wall->x)] - '0';
	scaled_y = (int)((ray->gfx.height / 2) - (BITS * (369 / distance)) + ray->height + (ray->player.height - 32));
	y = (int)((ray->gfx.height / 2) - ((16 * (height - 4)) * (350 / distance)) + ray->height + (ray->player.height - 32));
	y_max = (int)((ray->gfx.height / 2) + (BITS * (369 / distance)) + ray->height + (ray->player.height - 32));
	if (y < 0)
		y = 0;
	if (y_max > ray->gfx.height) 
		y_max = ray->gfx.height;
	if (y_max > wall->prev_y || y > wall->prev_y)
		y_max = wall->prev_y;
	if (y < wall->prev_y || y > ray->gfx.height )
		draw_ceiling(ray, *wall, wall->prev_y, screen);
	// if (height * 8 < 32)
	// 	draw_wall_top(ray, *wall, y - 1, screen);
	draw_floor(ray, *wall, y_max + 1, screen);
	draw_texture(ray, scaled_y, y_max, *wall, screen, y);
	if (y < wall->prev_y)
		wall->prev_y = y;
	SDL_FreeSurface(screen);
}
