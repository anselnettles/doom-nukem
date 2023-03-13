/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 17:27:53 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	split_delta_move_player2(t_drown *data, float *dir)
{
	if (data->system.keyboard_state[SDL_SCANCODE_A]
		&& !data->system.keyboard_state[SDL_SCANCODE_D])
	{
		*dir = 0.f - 90.f * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_W])
			*dir += 45 * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_S])
			*dir -= 45 * DEGREES;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_D]
		&& !data->system.keyboard_state[SDL_SCANCODE_A])
	{
		*dir = 0.f + 90.f * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_W])
			*dir -= 45 * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_S])
			*dir += 45 * DEGREES;
	}	
}

static void	split_delta_move_player1(t_drown *data, float *dir)
{
	if (data->system.keyboard_state[SDL_SCANCODE_A]
		|| data->system.keyboard_state[SDL_SCANCODE_W]
		|| data->system.keyboard_state[SDL_SCANCODE_D]
		|| data->system.keyboard_state[SDL_SCANCODE_S])
	{
		*dir = 0.f;
		if (data->player.velocity.x < 10)
			data->player.velocity.x += 2.f;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_S]
		&& !data->system.keyboard_state[SDL_SCANCODE_W])
		*dir = 0.f - 180.F * DEGREES;
}

void	delta_move_player(t_drown *data)
{
	static float	dir = 0.f;

	if (data->player.velocity.x >= 1)
		data->player.velocity.x -= 0.8f;
	else if (data->player.velocity.x < 2)
		data->player.velocity.x = 0;
	split_delta_move_player1(data, &dir);
	split_delta_move_player2(data, &dir);
	if (data->system.keyboard_state[SDL_SCANCODE_LSHIFT]
		&& data->player.velocity.x < 20)
		data->player.velocity.x *= 1.1;
	data->player.dx = cosf(data->player.dir + dir);
	data->player.dy = sinf(data->player.dir + dir);
}

static void	split_delta_time_move(t_drown *data)
{
	if (data->player.height <= data->player.base_height + data->player.altitude)
	{
		data->player.height = data->player.base_height + data->player.altitude;
		data->player.velocity.y = 0;
		data->player.in_air = 0;
	}
	if (data->player.height > 600)
		data->player.height = 600;
}

void	delta_time_move(t_drown *data)
{
	crouch(data);
	data->player.x -= data->player.velocity.x
		* data->system.frame_time * data->player.dx;
	data->player.y -= data->player.velocity.x
		* data->system.frame_time * data->player.dy;
	if (data->player.height
		< (data->map.map[(int)roundf((data->player.y - data->player.dy) / 64)]
			[(int)roundf((data->player.x - data->player.dx) / 64)][0] - '0')
			* 32 + data->player.base_height
		|| data->map.map[(int)roundf((data->player.y - data->player.dy) / 64)]
		[(int)roundf((data->player.x - data->player.dx) / 64)][0] == '#')
	{
		data->player.x += data->player.velocity.x
			* data->system.frame_time * data->player.dx;
		data->player.y += data->player.velocity.x
			* data->system.frame_time * data->player.dy;
	}
	data->player.altitude = (data->map.map[(int)roundf(data->player.y / 64)]
		[(int)roundf(data->player.x / 64)][0] - '0') * 32;
	data->player.velocity.y -= (GRAVITY / 2);
	data->player.height
		+= (data->player.velocity.y / 8) * data->system.frame_time;
	split_delta_time_move(data);
}
