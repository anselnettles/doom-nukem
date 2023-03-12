/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/09 16:56:17 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void		collect_airbottle(t_drown *d)
{
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	Mix_PlayChannel(-1, d->audio.inhale, 0);
	d->gfx.frame.right_arm = 3;
}

int		player_object_collision(t_drown *d, int s)
{
	if (d->map.map[(int)roundf(d->player.y / 64)]
		[(int)roundf(d->player.x / 64)][3] == 'Z')
		d->system.ending_state = REGULAR_ENDING;
	if (d->map.map[(int)roundf(d->player.y / 64)]
		[(int)roundf(d->player.x / 64)][3] == '$')
	{
		if (d->system.keyboard_state[SDL_SCANCODE_E])
		{
			d->map.map[(int)roundf(d->player.y / 64)]
			[(int)roundf(d->player.x / 64)][3] = '.';
			collect_airbottle(d);
		}
	}
		return (0);
}

int		get_value(t_map map, float x, float y, int z)
{
	if (map.map[(int)roundf(y / BITS)][(int)roundf(x / BITS)][z] == '.')
		return(0);
	return(map.map[(int)roundf(y / BITS)][(int)roundf(x / BITS)][z]);
}


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
	gfx->centre = ((gfx->width / 2) / tan(30 * DEGREES));
}

int	animation_loop(t_drown *d)
{
	right_arm_loop(d);
	hud_animation_loop(d);
	overworld_sprite_loop(d);
	flow_adjustment(d);
	return (0);
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
			Mix_PlayChannel(-1, d->audio.timer_hit, 0);
			d->system.five_second++;
			d->gfx.frame.bubble++;
		}
		d->system.frame_time = d->system.delta_time / 100.f;
		animation_loop(d);
}

void	crouch(t_drown *data)
{
	if (data->system.keyboard_state[SDL_SCANCODE_C])
		data->player.base_height = 16;
	else
		data->player.base_height = 32;
}

//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void		sdl_loop(t_drown *d)
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
			if (d->event.type == SDL_KEYDOWN || d->event.type == SDL_MOUSEMOTION)
				x_right_arm_flail(&d->gfx);
		}
		delta_move_player(d);
		delta_time_move(d);
		player_object_collision(d, d->gfx.scale);
		if (d->system.frame_time < 16.6666f)
			SDL_Delay(16.6666f - d->system.frame_time);
		draw_skybox(d);
		render(d);
		d->system.last_time = d->system.time;
	}
}
