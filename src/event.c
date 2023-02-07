/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:21:31 by tpaaso            #+#    #+#             */
/*   Updated: 2023/02/07 17:30:50 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	deal_key(t_drown *data)
{
	if (data->event.type == SDL_KEYDOWN)
	{
		if (data->keyboard[SDL_SCANCODE_ESCAPE])
			data->play_state = EXIT;
		
		if (data->keyboard[SDL_SCANCODE_A] ||data->keyboard[SDL_SCANCODE_D])
			strife(data);
		if (data->keyboard[SDL_SCANCODE_W] || data->keyboard[SDL_SCANCODE_S])
			move_player(data);
	}
	/*
	if (data->event.type == SDL_KEYUP)
	{
		if (key == SDLK_c)
			data->player.height = 32 + (data->map.map[(int)roundf(data->player.y)][(int)roundf(data->player.x)] - '0') * 8;
	}*/
	//if (SDL_GetKeyboardState)
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
	if (data->hg < -800)
		data->hg = -800;
}

void	move_player(t_drown *data)
{
	int		i;
	//int		height;

	i = 0;
	data->player.height = 32 + (data->map.map[(int)roundf(data->player.y)][(int)roundf(data->player.x)] - '0') * 8;
	while (i < SPEED)
	{
		if (data->keyboard[SDL_SCANCODE_W])
		{
			data->player.x -= data->player.dx;
			data->player.y -= data->player.dy;
		}
		if (data->keyboard[SDL_SCANCODE_S])
		{
			data->player.x += data->player.dx;
			data->player.y += data->player.dy;
		}
		if ((data->map.map[(int)roundf(data->player.y)][(int)roundf(data->player.x)] - '0') * 8 > data->player.height - 24 ||
		 data->map.map[(int)roundf(data->player.y)][(int)roundf(data->player.x)] == '#')
		{
			if (data->keyboard[SDL_SCANCODE_S])
			{
				data->player.x -= data->player.dx;
			data->player.y -= data->player.dy;
			}
			else
			{
				data->player.x += data->player.dx;
				data->player.y += data->player.dy;
			}
			i = SPEED;
		}
		i++;
	}
	data->player.x = roundf(data->player.x);
	data->player.y = roundf(data->player.y);
}

void	strife(t_drown *data)
{
	float	dx;
	float	dy;
	int		i;
	//int		height;


	i = 0;
	dx = cosf(data->player.dir + 90 * DEGREES);
	dy = sinf(data->player.dir + 90 * DEGREES);
	data->player.height = 32 + (data->map.map[(int)roundf(data->player.y)][(int)roundf(data->player.x)] - '0') * 8;
	while (i < SPEED)
	{
		if (data->keyboard[SDL_SCANCODE_D])
		{
			data->player.x -= dx;
			data->player.y -= dy;
		}
		if (data->keyboard[SDL_SCANCODE_A])
		{
			data->player.x += dx;
			data->player.y += dy;
		}
		if ((data->map.map[(int)roundf(data->player.y)][(int)roundf(data->player.x)] - '0') * 8 > data->player.height - 24 ||
		 data->map.map[(int)roundf(data->player.y)][(int)roundf(data->player.x)] == '#')
		{
			if (data->keyboard[SDL_SCANCODE_A])
			{
				data->player.x -= dx;
			data->player.y -= dy;
			}
			else
			{
				data->player.x += dx;
				data->player.y += dy;
			}
			i = SPEED;
		}
		i++;
	}
	data->player.x = roundf(data->player.x);
	data->player.y = roundf(data->player.y);
}
