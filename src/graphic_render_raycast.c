/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:49:19 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/08 12:32:11 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int		ft_diagonal_1(t_wall *wall, t_ray *ray)
{
	while (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '\\')
	{
		wall->x -= wall->dx;
		wall->y -= wall->dy;
		if ((int)roundf(wall->y) % 64 - (int)roundf(wall->x) % 64 == 0 || (int)roundf(wall->y) % 64 - (int)roundf(wall->x) % 64 == -1
			|| (int)roundf(wall->y) % 64 - (int)roundf(wall->x) % 64 == 1)
			return(1);
	}
	return(0);
}

int		ft_diagonal_2(t_wall *wall, t_ray *ray)
{
	while (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '<')
	{
		wall->x -= wall->dx;
		wall->y -= wall->dy;
		if ((int)roundf(wall->y) % 64 - (int)roundf(wall->x) % 64 == 0 || (int)roundf(wall->y) % 64 - (int)roundf(wall->x) % 64 == -1
			|| (int)roundf(wall->y) % 64 - (int)roundf(wall->x) % 64 == 1)
			return(1);
	}
	return(0);
}

int		ft_diagonal_3(t_wall *wall, t_ray *ray)
{
	while (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '/')
	{
		wall->x -= wall->dx;
		wall->y -= wall->dy;
		if ((int)roundf(wall->y) % 64 + (int)roundf(wall->x) % 64 == 64 || (int)roundf(wall->y) % 64 + (int)roundf(wall->x) % 64 == 65
			|| (int)roundf(wall->y) % 64 + (int)roundf(wall->x) % 64 == 63)
			return(1);
	}
	return(0);
}

int		ft_diagonal_4(t_wall *wall, t_ray *ray)
{
	while (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '>')
	{
		wall->x -= wall->dx;
		wall->y -= wall->dy;
		if ((int)roundf(wall->y) % 64 + (int)roundf(wall->x) % 64 == 64 || (int)roundf(wall->y) % 64 + (int)roundf(wall->x) % 64 == 65
			|| (int)roundf(wall->y) % 64 + (int)roundf(wall->x) % 64 == 63)
			return(1);
	}
	return(0);
}

int		ft_calc_diagonal(t_wall *wall, t_ray *ray)
{
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '\\')
		return(ft_diagonal_1(wall, ray));
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '<')
		return(ft_diagonal_2(wall, ray));
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '/')
		return(ft_diagonal_3(wall, ray));
	if (ray->map.map[(int)roundf(wall->y / BITS)][(int)roundf(wall->x / BITS)][2] == '>')
		return(ft_diagonal_4(wall, ray));
	return(0);
}

void	ft_bzero2(void *dst, size_t n)
{
	char	*s;

	s = dst;
	while (n)
	{
		*s = '0';
		s++;
		n--;
	}
}

void	init_new_wall(t_ray *ray, t_wall *wall)
{
	if (wall->dir > 2 * PI)
		wall->dir -= 2 * PI;
	if (wall->dir < 0)
		wall->dir += 2 * PI;
	wall->dx = cosf(wall->dir);
	wall->dy = sinf(wall->dir);
	wall->x = ray->player.x;
	wall->y = ray->player.y;
	wall->prev_y = ray->gfx.height;
}

void	*ft_raycast_thread(void  *args)
{
    t_ray		*ray;
	t_wall		wall;
	t_dda		dda;
	float	    distance;

    ray = args;
	ray->count = 0;
	wall.dir = ray->dir;
	wall.lock = (char *)malloc(sizeof(char) * ray->gfx.height + 1);
	if (wall.lock == NULL)
		exit(-1);
	wall.lock[ray->gfx.height] = '\0';
	ft_bzero2(wall.lock, ray->gfx.height - 1);
	while (ray->count < (ray->gfx.width / 6))
	{
		init_new_wall(ray, &wall);
		init_dda(ray, &wall, &dda);
		while (ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][0] != '#' && wall.prev_y > 0)
		//while (wall.x > 64.f && wall.y > 64.f && wall.x < 19.f * 64.f && wall.y < 19.f * 64.f)
		{
			// init_dda(ray, &wall, &dda);
			wall.distance = algo_dda(ray, &wall, &dda);
			wall.distance *= cosf(ray->player.dir - wall.dir);
			distance = wall.distance;
			draw_thread(ray, distance, &wall);
		}
		ft_bzero2(wall.lock, ray->gfx.height);
		wall.dir += (60 * DEGREES) / ray->gfx.width;
		ray->x++;
		ray->count++;
	}
	return (NULL);
}

void	init_thread(t_ray *ray, t_drown *data, int i)
{
	ray->count = 0;
	if (i == 0)
	{
		ray->x = 0;
		ray->dir = (data->player.dir - 30 * DEGREES);
	}
	if( i != 0)
	{
		ray->x = i * (data->gfx.width / 6);
		ray->dir = (data->player.dir - 30 * DEGREES) + (i * (data->gfx.width / 6) * (60 * DEGREES / data->gfx.width));
	}
	ray->height = data->gfx.centre;
	ray->gfx = data->gfx;
	ray->player = data->player;
	ray->map = data->map;
}

void    render_thread(t_drown *data)
{
    pthread_t threads[THREAD];
	t_ray	ray[THREAD];
    int     i;
    int     rc;

	i = 0;
    while (i < THREAD)
    {
		init_thread(&ray[i], data, i);
        rc = pthread_create(&threads[i], NULL, ft_raycast_thread, &ray[i]);
		i++;
    }
	i = 0;
	while (i < THREAD)
	{
		rc = pthread_join(threads[i], NULL);
		i++;
	}
}
