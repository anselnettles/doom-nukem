/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/17 15:44:26 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void		scale_window(t_gfx *gfx)
{
	if (gfx->scale == 1)
		gfx->scale = 2;
	else
		gfx->scale = 1;
	gfx->width = (WIDTH * gfx->scale);
	gfx->height = (HEIGHT * gfx->scale);
	SDL_SetWindowSize(gfx->window, gfx->width, gfx->height);
	gfx->screen = SDL_GetWindowSurface(gfx->window);
	gfx->dop = gfx->width / 2 / tan(30 * DEGREES);
}

static void	track_time(t_drown *d)
{
		d->system.time = SDL_GetTicks();
		d->system.delta_time = (d->system.time - d->system.last_time);
		if ((d->system.time / 1000) >= d->system.second)
				d->system.second++;
		if ((d->system.second / 5 >= d->system.five_second)
				&& (d->gfx.frame.bubble < 13))
		{
			d->system.five_second++;
			d->gfx.frame.bubble++;
		}
		d->system.frame_time = d->system.delta_time / 100.f;
		//printf("frame_time = %f\n", d->system.frame_time);
		animation_loop(d);
}

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
			|| data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)] == '#')
		{
			data->player.x += data->player.velocity.x * data->system.frame_time * data->player.dx;
			data->player.y += data->player.velocity.x * data->system.frame_time * data->player.dy;
		}
		data->player.base_height = 32 + (data->map.map[(int)roundf(data->player.y / 64)][(int)roundf(data->player.x / 64)][0] - '0') * 8;
}


//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void		sdl_loop(t_drown *d)
{
	d->system.keyboard_state = SDL_GetKeyboardState(NULL);
	while (d->system.play_state == PLAY)
	{
		d->player.velocity.y -= GRAVITY;
		d->player.height += d->player.velocity.y * d->system.frame_time;
		if (d->player.height <= d->player.base_height)
		{
			d->player.height = d->player.base_height;
			d->player.velocity.y = 0;
			d->player.in_air = 0;
		}
		track_time(d);
		while (SDL_PollEvent(&d->event) != 0)
		{
			if (d->event.type == SDL_QUIT)
				d->system.play_state = EXIT;
			else if (d->event.type == SDL_KEYDOWN)
				deal_key(d->event.key.keysym.sym, d);
			else if (d->event.type == SDL_MOUSEMOTION)
				deal_mouse(d);
			if (d->event.type == SDL_KEYDOWN || d->event.type == SDL_MOUSEMOTION)
				x_right_arm_flail(&d->gfx);
		}
		/*if (d->system.keyboard_state[SDL_SCANCODE_W])
			delta_time_move(d);*/
		delta_move_player(d);
		delta_time_move(d);
		//strife(d);
		if (d->system.frame_time < 16.6666f)			//OPTIMOI MINUT
		{
			SDL_Delay(16.6666f - d->system.frame_time);
		}
			render(d);
			d->system.last_time = d->system.time;
		
	}
}
