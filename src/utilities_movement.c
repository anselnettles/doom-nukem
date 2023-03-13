/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 13:33:45 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	crouch(t_drown *data)
{
	if (data->system.keyboard_state[SDL_SCANCODE_C])
		data->player.base_height = 16;
	else
		data->player.base_height = 32;
}

void	delta_move_player(t_drown *data)
{
	static float			dir = 0.f;

	if (data->player.velocity.x >= 1)
		data->player.velocity.x -= 0.8f;
	else if (data->player.velocity.x < 2)
		data->player.velocity.x = 0;
//	dir -= 0.1f;
	//dir = 0.f;
	if (data->system.keyboard_state[SDL_SCANCODE_A] || data->system.keyboard_state[SDL_SCANCODE_W]
		|| data->system.keyboard_state[SDL_SCANCODE_D] ||data->system.keyboard_state[SDL_SCANCODE_S])
	{
		dir = 0.f;
		if (data->player.velocity.x < 10)
			data->player.velocity.x += 2.f;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_S]  && !data->system.keyboard_state[SDL_SCANCODE_W])
	{
		dir = 0.f;
		dir -= 180.F * DEGREES;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_A]  && !data->system.keyboard_state[SDL_SCANCODE_D])
	{
		dir = 0.f;
		dir -= 90.f * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_W])
		{
			dir += 45 * DEGREES;
		}
		if (data->system.keyboard_state[SDL_SCANCODE_S])
			dir -= 45 * DEGREES;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_D]  && !data->system.keyboard_state[SDL_SCANCODE_A])
	{
		dir = 0.f;
		dir += 90.f * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_W])
			dir -= 45 * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_S])
			dir += 45 * DEGREES;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_LSHIFT] && data->player.velocity.x < 20)
		data->player.velocity.x *= 1.1;
	data->player.dx = cosf(data->player.dir + dir);
	data->player.dy = sinf(data->player.dir + dir);
}

void	delta_time_move(t_drown *data)
{
		crouch(data);
		data->player.x -= data->player.velocity.x * data->system.frame_time * data->player.dx;
		data->player.y -= data->player.velocity.x * data->system.frame_time * data->player.dy;
		while (data->player.height < (data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)][0] - '0') * 8
			|| data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)][0] == '#')
		{
			data->player.x += data->player.velocity.x * data->system.frame_time * data->player.dx;
			data->player.y += data->player.velocity.x * data->system.frame_time * data->player.dy;
		}
		//KORJAA TAMA >
		data->player.altitude = (data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)][0] - '0') * 32;
		data->player.velocity.y -= (GRAVITY / 2);
		data->player.height += (data->player.velocity.y / 8) * data->system.frame_time;
		if (data->player.height <= data->player.base_height + data->player.altitude)
		{
			data->player.height = data->player.base_height + data->player.altitude;
			data->player.velocity.y = 0;
			data->player.in_air = 0;
		}
		if (data->player.height > 600)
			data->player.height = 600;
}
