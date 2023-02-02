/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:45:29 by tpaaso            #+#    #+#             */
/*   Updated: 2023/02/02 15:54:08 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"
#include <stdlib.h>

void	pixel_put(SDL_Surface *screen, int x, int y, Uint32 color)
{
	uint32_t	*pix;

	pix = screen->pixels;
	pix[x + ((y) * WIDTH)] = color;
}

void	draw_collumn(t_ray *ray, int y, int y_max, Uint32 color, SDL_Surface *screen)
{
	if (y_max > HEIGHT)
		y_max = HEIGHT;
	while (y < y_max && y >= 0)
	{
		pixel_put(screen, ray->x, y, color);
		y++;
	}
}

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

	texture = big_checkerboard(SDL_MapRGB(screen->format, 0xF7, 0xCE, 0x00), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	i = (float)(y_max - y) / 64;
//	if (i < 1)
//		i = 1;
	j = 0;
	texture_y = 0;
	texture_x = (int)wall.x % 64;
	if (ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x + 1 )] == '0'
		|| ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x - 1 )] == '0')
		texture_x = (int)wall.y % 64;
	while (y <= y_max && texture_y < 64)
	{
		if (j > i)
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
	texture = big_checkerboard(SDL_MapRGB(screen->format, 0xF7, 0xCE, 0x00), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	while (win_y < HEIGHT)
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
	texture = big_checkerboard(SDL_MapRGB(screen->format, 0xF7, 0xCE, 0x00), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	//texture = create_checkerboard(SDL_MapRGB(screen->format, 0xF7, 0xCE, 0x00), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
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

void	draw_thread(t_ray *ray, float distance, t_wall wall)
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
	height =  ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x)] - '0';
	height -= 4;
	scaled_y = (int)((HEIGHT / 2) - (BITS * (600 / distance)) + ray->height);
	y = (int)((HEIGHT / 2) - ((16 * height) * (600 / distance)) + ray->height);
	y_max = (int)((HEIGHT / 2) + (BITS * (600 / distance)) + ray->height);
	if (y < 0)
		y = 0;
	if (y_max > HEIGHT)
		y_max = HEIGHT;
	draw_ceiling(ray, wall, y, screen);
	draw_texture(ray, scaled_y, y_max, wall, screen, y);
	draw_floor(ray, wall, y_max, screen);
	SDL_FreeSurface(screen);
}

int		get_modulo(t_wall wall)
{
	int		modul_x;
	int		modul_y;

	modul_x = (int)roundf(wall.x) % 64;
	modul_y = (int)roundf(wall.y) % 64;
	if (wall.dx < 0)
		modul_x = 64 - modul_x;
	if (modul_x == 0)
	{
		return(1);
	}
	if (wall.dy < 0)
		modul_y = 64 - modul_y;
	if (modul_y == 0)
	{
		return(1);
	}
	if (modul_y < modul_x)
		return (modul_y);
	return (modul_x);
}
void	*ft_raycast_thread(void  *args)
{
    t_ray		*ray;
	t_wall		wall;
	float	    distance;
	int			modul;

    ray = args;
	distance = 0;
	ray->count = 0;
	wall.dir = ray->dir;
	modul = 0;
	while (ray->count < THREADRAY)
	{
		if (wall.dir > 2 * PI)
			wall.dir -= 2 * PI;
		if (wall.dir < 0)
			wall.dir += 2 * PI;
		wall.dx = cosf(wall.dir);
		wall.dy = sinf(wall.dir);
		wall.x = ray->player.x;
		wall.y = ray->player.y;
		modul = get_modulo(wall);
		while (ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x)] ==
			ray->map.map[(int)roundf(ray->player.y)][(int)roundf(ray->player.x)])
		{
			modul = get_modulo(wall);
			wall.x -= wall.dx * modul;
			wall.y -= wall.dy * modul;
		}
		distance = sqrtf(((wall.x - ray->player.x) * (wall.x - ray->player.x))
			+ ((wall.y - ray->player.y) * (wall.y - ray->player.y)));
		distance *= cosf(ray->player.dir - wall.dir);
		draw_thread(ray, distance, wall);
		wall.dir += (60 * DEGREES) / WIDTH;
		ray->x++;
		ray->count++;
	}
	return (NULL);
}


void    render_thread(t_drown *data)
{
    pthread_t threads[THREAD];
	t_ray	ray[THREAD];
    int     i;
    int     rc;

	i = 0;
	ray[0].x = 0;
	ray[i].dir = (data->player.dir - 30 * DEGREES);
    while (i < THREAD)
    {
		ray[i].count = 0;
		if( i != 0)
		{
			ray[i].x = i * THREADRAY;
			ray[i].dir = (data->player.dir - 30 * DEGREES) + (i * THREADRAY * (60 * DEGREES / WIDTH));
		}
		ray[i].height = data->hg;
		ray[i].window = data->gfx.window;
		ray[i].player = data->player;
		ray[i].map = data->map;
        rc = pthread_create(&threads[i], NULL, ft_raycast_thread, &ray[i]);
		i++;
    }
	i = 0;
	while (i <= THREAD)
	{
		rc = pthread_join(threads[i], NULL);
		i++;
	}
}
