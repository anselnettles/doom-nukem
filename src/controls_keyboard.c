/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 13:03:42 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	scale_window(t_gfx *gfx)
{
	if (gfx->scale == 1)
		gfx->scale = 2;
	else
		gfx->scale = 1;
	gfx->width = (WIDTH * gfx->scale);
	gfx->height = (HEIGHT * gfx->scale);
	SDL_SetWindowSize(gfx->window, gfx->width, gfx->height);
	gfx->screen = SDL_GetWindowSurface(gfx->window);
	gfx->centre = ((gfx->width / 2) / tan(30 * DEGREES));
}

void	deal_key(int key, t_drown *data)
{
	if (data->system.keyboard_state[SDL_SCANCODE_ESCAPE])
		data->system.play_state = EXIT;
	if (data->system.keyboard_state[SDL_SCANCODE_F1])
		scale_window(&data->gfx);
	if (key == SDLK_SPACE && data->player.in_air == 0)
	{
		data->player.velocity.y = 70.f;
		if (data->system.overlay_toggle == TRUE)
			data->player.in_air = 1;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_F2])
	{
		if (data->system.filters == TRUE)
			data->system.filters = FALSE;
		else
			data->system.filters = TRUE;
	}
	if (data->system.keyboard_state[SDL_SCANCODE_F3])
		data->system.overlay_toggle = -data->system.overlay_toggle;
	if (data->system.keyboard_state[SDL_SCANCODE_F5]
		&& data->gfx.frame.bubble > 1)
		collect_airbottle(data);
}

// void	move_forward_back(t_drown *data)
// {
// 	int		i;
// 	int		sprint;

// 	i = 0;
// 	sprint = 1;
// 	if (data->system.keyboard_state[SDL_SCANCODE_LSHIFT])
// 		sprint = 2;
// 	while (i < SPEED * sprint)
// 	{
// 		if (data->system.keyboard_state[SDL_SCANCODE_W])
// 		{
// 			data->player.x -= data->player.dx;
// 			data->player.y -= data->player.dy;
// 		}
// 		if (data->system.keyboard_state[SDL_SCANCODE_S])
// 		{
// 			data->player.x += data->player.dx;
// 			data->player.y += data->player.dy;
// 		}
// 		if ((data->map.map[(int)roundf(data->player.y
// 						/ BITS)][(int)roundf(data->player.x / BITS)][0] - '0')
// 				* 8 > data->player.height - 24
// 				|| data->map.map[(int)roundf(data->player.y / BITS)]
// 			[(int)roundf(data->player.x / BITS)][0] == '#')
// 		{
// 			if (data->system.keyboard_state[SDL_SCANCODE_S])
// 			{
// 				data->player.x -= data->player.dx;
// 			data->player.y -= data->player.dy;
// 			}
// 			else
// 			{
// 				data->player.x += data->player.dx;
// 				data->player.y += data->player.dy;
// 			}
// 			i = SPEED * sprint;
// 		}
// 		i++;
// 	}
// 	if (data->system.overlay_toggle == TRUE)
// 	data->player.height
// 		= data->player.base_height
// 		+ (data->map.map[(int)roundf(data->player.y / BITS)]
// 		[(int)roundf(data->player.x / BITS)][0] - '0') * 8.f;
// 	/*data->player.altitude = (data->map.map[(int)roundf(data->player.y / BITS)]
// 		[(int)roundf(data->player.x / BITS)][0] - '0') * 8.f;*/
// 	data->player.x = roundf(data->player.x);
// 	data->player.y = roundf(data->player.y);
// 	y_right_arm_flail(&data->gfx);
// }

// void	move_strafe(t_drown *data)
// {
// 	float	dx;
// 	float	dy;
// 	int		i;

// 	i = 0;
// 	dx = cosf(data->player.dir + 90 * DEGREES);
// 	dy = sinf(data->player.dir + 90 * DEGREES);
// 	while (i < SPEED)
// 	{
// 		if (data->system.keyboard_state[SDL_SCANCODE_A])
// 		{
// 			data->player.x += dx;
// 			data->player.y += dy;
// 		}
// 		if (data->system.keyboard_state[SDL_SCANCODE_D])
// 		{
// 			data->player.x -= dx;
// 			data->player.y -= dy;
// 		}
// 		if ((data->map.map[(int)roundf(data->player.y / BITS)]
// 				[(int)roundf(data->player.x / BITS)]
// 				[0] - '0') * 8 > data->player.height - 24
// 				|| data->map.map[(int)roundf(data->player.y / BITS)]
// 				[(int)roundf(data->player.x / BITS)][0] == '#')
// 		{
// 			if (data->system.keyboard_state[SDL_SCANCODE_A])
// 			{
// 				data->player.x -= dx;
// 				data->player.y -= dy;
// 			}
// 			else
// 			{
// 				data->player.x += dx;
// 				data->player.y += dy;
// 			}
// 			i = SPEED;
// 		}
// 		i++;
// 	}
// 	if (data->system.overlay_toggle == TRUE)
// 	data->player.height
// 		= data->player.base_height
// 		+ (data->map.map[(int)roundf(data->player.y / BITS)]
// 			[(int)roundf(data->player.x / BITS)][0] - '0') * 8;
// 	/*data->player.altitude = (data->map.map[(int)roundf(data->player.y / BITS)]
// 		[(int)roundf(data->player.x / BITS)][0] - '0') * 8.f;*/
// 	data->player.x = roundf(data->player.x);
// 	data->player.y = roundf(data->player.y);
// }
