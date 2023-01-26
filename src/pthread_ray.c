/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:45:29 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/26 16:45:05 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	pixel_put(SDL_Surface *screen, int x, int y, Uint32 color)
{
	uint32_t	*pix;

	pix = screen->pixels;
	pix[x + ((y) * WIDTH)] = color;
}

void	draw_collumn(t_ray *ray, int y, int y_max, Uint32 color)
{
	SDL_Surface *screen;

	if (!(screen = SDL_GetWindowSurface(ray->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	while (y < y_max)
	{
		pixel_put(screen, ray->x, y, color);
		y++;
	}
	SDL_FreeSurface(screen);
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
		while (x <= 64)
		{
			if (x < 32)
				texture.texture[y][x] = color_one;
			else
				texture.texture[y][x] = color_two;
			x++;
		}
		y++;
	}
	while (y <= 64)
	{
		x = 0;
		while (x <= 64)
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

void	draw_texture(t_ray *ray, int y, int y_max, t_player wall)
{
	SDL_Surface *screen;
	t_texture	texture;
	int			texture_y;
	int			texture_x;
	float		i;
	int			j;

	if (!(screen = SDL_GetWindowSurface(ray->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	texture = create_checkerboard(SDL_MapRGB(screen->format, 0xF7, 0xCE, 0x00), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	i = (y_max - y) / 64;
	if (i < 1)
		i = 1;
	j = 0;
	texture_y = 0;
	texture_x = (int)wall.x % 64;
	if (ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x + 1 )] == ' '
		|| ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x - 1 )] == ' ')
		texture_x = (int)wall.y % 64;
	//if (y < 0)
	//	y = 0;
	while (y < y_max && texture_y < 64 && y < HEIGHT)
	{
		if (j > i)
		{
			j = 0;
			texture_y += 1;
		}
		if (y >= 0 && y < HEIGHT)
			pixel_put(screen, ray->x, y, texture.texture[texture_y][texture_x]);
		y++;
		j++;
	}
	SDL_FreeSurface(screen);
}

void	draw_floor(t_ray *ray, t_player wall, int win_y)
{
	SDL_Surface *screen;
	t_texture texture;
	int x;
	int y;
	float dy;
	float dx;
	float distance;
	float	dir;

	dx = 0;
	dy = 0;
	if (!(screen = SDL_GetWindowSurface(ray->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	texture = big_checkerboard(SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF), SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	//dir = atanf((y - height -  2) / distance);
	dir = tanf(32);
	distance = 32 * tanf(dir);
	distance *= cosf(ray->player.dir - ray->dir);
	//printf("actual distance is %f, my distance is %f\n", sqrt((wall.x - ray->player.x) * (wall.x - ray->player.x) + (wall.y - ray->player.y) * (wall.y - ray->player.y)), distance);
	while (win_y < HEIGHT)
	{
		//calculate direction from eye to pixel;
		//distance to pixel is sin/cos/tan(playerheight * direction)
		//dir -= 0.1 * DEGREES;//atanf(32 / (win_y - 400));
		distance = 32 * dir;
		distance *= cosf(ray->player.dir - wall.dir);
		x = (int)(wall.dx * distance);
		y = (int)(wall.dy * distance);
		pixel_put(screen, ray->x, win_y, texture.texture[y % 64][x % 64]);
		win_y++;
	}
}

void	draw_thread(t_ray *ray, float distance, t_player wall)
{
	SDL_Surface *screen;
	//t_texture	floor_texture;
	int			y;
	int			y_max;

	//floor_texture = create_texture()
	if (!(screen = SDL_GetWindowSurface(ray->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	if (distance < 1)
		distance = 1;
	y = (int)((HEIGHT / 2) - (BITS * (554 / distance)) + ray->height);
	y_max = (int)((HEIGHT / 2) + (BITS * (554 / distance)) + ray->height);
	if (y < 0)
		y = 0;
	if (y_max > HEIGHT)
		y_max = HEIGHT;
	draw_collumn(ray, 0, y, SDL_MapRGB(screen->format, 0x03, 0xD3, 0xFC)); // draw sky
	draw_texture(ray, y, y_max, wall);
	//draw_floor(ray, wall, y_max);
	//draw_collumn(ray, y, y_max, get_color(wall, screen, distance));			//draw wall
	//draw_collumn(ray, y_max, HEIGHT, SDL_MapRGB(screen->format, 0xFC, 0xC6, 0x03)); //draw floor
	SDL_FreeSurface(screen);
}


void	*ft_raycast_thread(void  *args)
{
    t_ray		*ray;
	t_player	wall;
	float	    distance;

    ray = args;
	distance = 0;
	ray->count = 0;
	wall.dir = ray->dir;
	while (ray->count < THREADRAY)
	{
		if (wall.dir > 2 * PI)
			wall.dir -= 2 * PI;
		if (wall.dir < 0)
			wall.dir += 2 * PI;
		wall.x = ray->player.x;
		wall.y = ray->player.y;
		wall.dx = cosf(wall.dir);
		wall.dy = sinf(wall.dir);
		while (ray->map.map[(int)roundf(wall.y)][(int)roundf(wall.x)] == ' ')
		{
			wall.x -= wall.dx;
			wall.y -= wall.dy;
		}
		ray->distance = sqrtf(((wall.x - ray->player.x) * (wall.x - ray->player.x))
			+ ((wall.y - ray->player.y) * (wall.y - ray->player.y)));
		ray->distance *= cosf(ray->player.dir - wall.dir);
		draw_thread(ray, ray->distance, wall);
		wall.dir += (60 * DEGREES) / WIDTH;
		ray->x++;
		ray->count++;
	}
	return (NULL);
}

void    render_thread(t_main *data)
{
    pthread_t threads[THREAD];
	t_ray	ray[THREAD];
	SDL_Surface	*screen;
	SDL_Rect	rect;
    int     i;
    int     rc;

	i = 0;
		if (!(screen = SDL_GetWindowSurface(data->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	rect.w = 1;
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
		ray[i].height = data->height;
		ray[i].window = data->window;
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
	i = 0;
	SDL_FreeSurface(screen);
}
