/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_raycast.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:49:19 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/20 13:33:56 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"
/*
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
*/

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

void	*ft_raycast_thread(void  *args)
{
    t_ray		*ray;
	t_wall		wall;
	float	    distance;
//	int			modul;
	int			remember;

    ray = args;
	ray->count = 0;
	wall.dir = ray->dir;
	wall.prev_y = ray->gfx.height;
	while (ray->count < (ray->gfx.width / 6))
	{
		if (wall.dir > 2 * PI)
			wall.dir -= 2 * PI;
		if (wall.dir < 0)
			wall.dir += 2 * PI;
		wall.dx = cosf(wall.dir);
		wall.dy = sinf(wall.dir);
		wall.x = ray->player.x;
		wall.y = ray->player.y;
		wall.prev_y = ray->gfx.height;
		remember = ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][0] - '0';
		while (ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][0] != '#')
		{
			remember = ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][0] - '0';
			while (ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][0] - '0' == remember)
			{
//				modul = get_modulo(wall);
//				modul = 1;
				wall.x -= wall.dx;// * modul;
				wall.y -= wall.dy;// * modul;
				if (ray->map.map[(int)roundf(wall.y / BITS)][(int)roundf(wall.x / BITS)][2] != '.')
					if (ft_calc_diagonal(&wall, ray))
						break ;
			}
			distance = sqrtf(((wall.x - ray->player.x) * (wall.x - ray->player.x))
				+ ((wall.y - ray->player.y) * (wall.y - ray->player.y)));
			distance *= cosf(ray->player.dir - wall.dir);
			draw_thread(ray, distance, &wall);
		}
		wall.dir += (60 * DEGREES) / ray->gfx.width;
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
			ray[i].x = i * (data->gfx.width / 6);
			ray[i].dir = (data->player.dir - 30 * DEGREES) + (i * (data->gfx.width / 6) * (60 * DEGREES / data->gfx.width));
		}
		ray[i].height = data->gfx.centre;
		ray[i].gfx = data->gfx;
		ray[i].player = data->player;
		ray[i].map = data->map;
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
