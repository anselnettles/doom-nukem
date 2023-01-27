/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:21:31 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/27 21:10:52 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	deal_key(int key, t_drown *data)
{
	if (key == SDLK_ESCAPE)
		data->option = EXIT;
	if (key == SDLK_0)
		draw_map(data);
	if (key == SDLK_a || key == SDLK_d)
		strife(key, &data->player, data->map);
	if (key == SDLK_w || key == SDLK_s)
		move_player(key, &data->player, data->map);
}

void	deal_mouse(t_drown *data)
{
	data->player.dir += data->event.motion.xrel * DEGREES / 2;
	if (data->player.dir > 2 * PI)
		data->player.dir -= 2 * PI;
	if (data->player.dir < 0)
		data->player.dir += 2 * PI;
	data->player.dx = cosf(data->player.dir);
	data->player.dy = sinf(data->player.dir);
	data->hg -= data->event.motion.yrel * 8;
	if (data->hg > 700)
		data->hg = 700;
	if (data->hg < -400)
		data->hg = -400;
//	clear_screen(data);
//	render_thread(data);
//	draw_map(data);
//	SDL_UpdateWindowSurface(data->window);
}

void	move_player(int key, t_player *player, t_map map)
{
	int		i;

	i = 0;
	while (i < SPEED)
	{
		if (key == SDLK_w)
		{
			player->x -= player->dx;
			player->y -= player->dy;
		}
		if (key == SDLK_s)
		{
			player->x += player->dx;
			player->y += player->dy;
		}
		if (map.map[(int)roundf(player->y)][(int)roundf(player->x)] != ' ')
		{
			if (key == SDLK_s)
			{
				player->x -= player->dx;
				player->y -= player->dy;
			}
			else
			{
				player->x += player->dx;
				player->y += player->dy;
			}
			i = SPEED;
		}
		i++;
	}
	player->x = roundf(player->x);
	player->y = roundf(player->y);
}

void	strife(int key, t_player *player, t_map map)
{
	float	dx;
	float	dy;
	int		i;


	i = 0;
	dx = cosf(player->dir + 90 * DEGREES);
	dy = sinf(player->dir + 90 * DEGREES);
	while (i < SPEED)
	{
		if (key == SDLK_a)
		{
			player->x += dx;
			player->y += dy;
		}
		if (key == SDLK_d)
		{
			player->x -= dx;
			player->y -= dy;
		}
		if (map.map[(int)roundf(player->y)][(int)roundf(player->x)] != ' ')
		{
			if (key == SDLK_a)
			{
				player->x -= dx;
				player->y -= dy;
			}
			else
			{
				player->x += dx;
				player->y += dy;
			}
			i = SPEED;
		}
		i++;
	}
	player->x = roundf(player->x);
	player->y = roundf(player->y);
}
