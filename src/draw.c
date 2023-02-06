/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 10:03:55 by tpaaso            #+#    #+#             */
/*   Updated: 2023/02/04 12:06:59 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"
t_texture	create_checkerboard(Uint32 color_one, Uint32 color_two)
{
	t_texture	texture;
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

t_texture	big_checkerboard(Uint32 color_one, Uint32 color_two)
{
	t_texture	texture;
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
	t_texture	texture;
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
		if (y >= 0 && y < HEIGHT && y >= limiter)
			pixel_put(screen, ray->x, y, texture.texture[texture_y][texture_x]);
		y++;
		j++;
	}
}

void	draw_floor(t_ray *ray, t_wall wall, int win_y, SDL_Surface *screen)
{
	t_texture texture;
	float x;
	float y;
	float dy;
	float dx;
	int tx;
	int ty;
	float distance;
	float	dir;

	dx = cosf(wall.dir);
	dy = sinf(wall.dir);
	texture = big_checkerboard(SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	while (win_y < wall.prev_y && win_y < HEIGHT)
	{
		dir = atanf((float)(win_y - 400 - ray->height) / (float)1108);
		distance = (float)32 / dir;
		distance /= cosf(ray->player.dir - wall.dir);
		x = ray->player.x - dx * distance;
		y = ray->player.y - dy * distance;
		tx = (int)roundf(y) % 64;
		ty = (int)roundf(x) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y > 0)
			pixel_put(screen, ray->x, win_y, texture.texture[ty][tx]);
		win_y++;
	}
}

void	draw_ceiling(t_ray *ray, t_wall wall, int win_y, SDL_Surface *screen)
{
	t_texture texture;
	float x;
	float y;
	float dy;
	float dx;
	int tx;
	int ty;
	float distance;
	float	dir;

	dx = cosf(wall.dir);
	dy = sinf(wall.dir);
	texture = big_checkerboard(SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	while (win_y >= 0)
	{
		dir = atanf((float)(win_y - 400 - ray->height) / (float)1108);
		distance = (float)32 / dir;
		distance /= cosf(ray->player.dir - wall.dir);
		x = ray->player.x + dx * distance;
		y = ray->player.y + dy * distance;
		tx = (int)roundf(y) % 64;
		ty = (int)roundf(x) % 64;
		if (tx < 0)
			tx *= -1;
		if (ty < 0)
			ty *= -1;
		if (win_y < HEIGHT)
			pixel_put(screen, ray->x, win_y, texture.texture[ty][tx]);
		win_y--;
	}
}

void	draw_thread(t_ray *ray, float distance, t_wall *wall)
{
	SDL_Surface *screen;
	int			y;
	int			y_max;
	int 		height;
	int			scaled_y;

	if (!(screen = SDL_GetWindowSurface(ray->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	if (distance < 1)
		distance = 1;
	height =  ray->map.map[(int)roundf(wall->y)][(int)roundf(wall->x)] - '0';
	height -= 4;
	scaled_y = (int)((HEIGHT / 2) - (BITS * (600 / distance)) + ray->height);
	y = (int)((HEIGHT / 2) - ((16 * height) * (600 / distance)) + ray->height);
	y_max = (int)((HEIGHT / 2) + (BITS * (600 / distance)) + ray->height);
	if (y < 0)
		y = 0;
	if (y_max > HEIGHT)
		y_max = HEIGHT;
	if (y_max > wall->prev_y || y > wall->prev_y)
		y_max = wall->prev_y;
	draw_texture(ray, scaled_y, y_max, *wall, screen, y);
	if (y <= wall->prev_y || y >= HEIGHT)
		draw_ceiling(ray, *wall, y, screen);
	draw_floor(ray, *wall, y_max, screen);
	wall->prev_y = y;
	SDL_FreeSurface(screen);
}
