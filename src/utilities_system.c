/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/22 14:16:23 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	get_value(t_map map, float x, float y, int z)
{
	int		tmp;

	if ((int)roundf(x / 64) >= 28 || (int)roundf(y / 64) >= 20
		|| y <= 0 || x <= 0)
		return (0);
	if (map.map[(int)roundf(y / BITS)][(int)roundf(x / BITS)][z] == '.')
		return (0);
	if (z == 1)
	{
		tmp = map.map[(int)roundf(y / BITS)][(int)roundf(x / BITS)][z] - 'a';
		if (tmp < 4 && tmp >= 0)
			return (tmp);
		else
			return (0);
	}
	return (map.map[(int)roundf(y / BITS)][(int)roundf(x / BITS)][z]);
}

int	animation_loop(t_drown *d)
{
	right_arm_loop(d);
	left_arm_loop(d);
	hud_animation_loop(d);
	overworld_sprite_loop(d);
	flow_adjustment(d);
	return (0);
}

static void	track_time(t_drown *d)
{
	d->system.time = (SDL_GetTicks() - d->system.start_time);
	d->system.delta_time = (d->system.time - d->system.last_time);
	if ((d->system.time / 1000) >= d->system.second)
		d->system.second++;
	if ((d->system.second / 5 >= d->system.five_second)
		&& (d->gfx.frame.bubble < 13))
	{
		Mix_PlayChannel(-1, d->audio.timer_hit, 0);
		d->system.five_second++;
		d->gfx.frame.bubble++;
		if (d->gfx.frame.bubble < 13)
			d->gfx.frame.bubble += d->system.hard_mode;
	}
	d->system.frame_time = d->system.delta_time / 100.f;
	animation_loop(d);
}

//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void	sdl_loop(t_drown *d)
{
	d->system.keyboard_state = SDL_GetKeyboardState(NULL);
	while (d->system.play_state == PLAY)
	{
		track_time(d);
		while (SDL_PollEvent(&d->event) != 0)
		{
			if (d->event.type == SDL_QUIT)
				d->system.play_state = EXIT;
			else if (d->event.type == SDL_KEYDOWN)
				deal_key(d->event.key.keysym.sym, d);
			else if (d->event.type == SDL_MOUSEMOTION)
				deal_mouse(d);
			if (d->event.type == SDL_KEYDOWN
				|| d->event.type == SDL_MOUSEMOTION)
				x_right_arm_flail(&d->gfx);
		}
		delta_move_player(d);
		delta_time_move(d);
		player_object_collision(d);
		if (d->system.frame_time < 16.6666f)
			SDL_Delay(16.6666f - d->system.frame_time);
		draw_skybox(d);
		render(d);
		d->system.last_time = d->system.time;
	}
}
