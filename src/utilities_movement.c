/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/06 09:49:42 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	delta_move_player(t_drown *data)
{
	float	dir;
	data->player.velocity.x = 0.f;
	dir = 0.f;
	if (data->system.keyboard_state[SDL_SCANCODE_A] || data->system.keyboard_state[SDL_SCANCODE_W]
		|| data->system.keyboard_state[SDL_SCANCODE_D] ||data->system.keyboard_state[SDL_SCANCODE_S])
		data->player.velocity.x = 30.f;
	if (data->system.keyboard_state[SDL_SCANCODE_S]  && !data->system.keyboard_state[SDL_SCANCODE_W])
		dir -= 180.F * DEGREES;
	if (data->system.keyboard_state[SDL_SCANCODE_A]  && !data->system.keyboard_state[SDL_SCANCODE_D])
	{
		dir = 0.f;
		dir -= 90.f * DEGREES;
		if (data->system.keyboard_state[SDL_SCANCODE_W])
			dir += 45 * DEGREES;
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
	if (data->system.keyboard_state[SDL_SCANCODE_LSHIFT])
		data->player.velocity.x *= 2;
	data->player.dx = cosf(data->player.dir + dir);
	data->player.dy = sinf(data->player.dir + dir);
}

void	delta_time_move(t_drown *data)
{
		data->player.x -= data->player.velocity.x * data->system.frame_time * data->player.dx;
		data->player.y -= data->player.velocity.x * data->system.frame_time * data->player.dy;
		while (data->player.height < (data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)][0] - '0') * 8
			|| data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)][0] == '#')
		{
			data->player.x += data->player.velocity.x * data->system.frame_time * data->player.dx;
			data->player.y += data->player.velocity.x * data->system.frame_time * data->player.dy;
		}
		data->player.base_height = 32 + (data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)][0] - '0') * 8;
}
