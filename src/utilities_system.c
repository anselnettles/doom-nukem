/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/03 19:21:27 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void		collect_airbottle(t_drown *d)
{
	//called by draw thread() when player collides to item 'I'(?)
	//remove item from map/draw;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	if (d->gfx.frame.bubble > 0)
		d->gfx.frame.bubble--;
	//play sound effect;
	d->gfx.frame.right_arm = 3;
	//overlay effect;
}

void	goal_point(t_drown *d)
{
	gfx_write(&d->gfx, "CONGRATULATIONS! YOU ESCAPED!");
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

void	crouch(t_drown *data)
{
	if (data->system.keyboard_state[SDL_SCANCODE_C])
		data->player.base_height = 16;
	else
		data->player.base_height = 32;
}

void	draw_skybox_collumn(t_drown *data, int x, int tx)
{
	int		y;
	int		ty;
	int		i;
	int		stretch;

	y = 0;
	ty = 0;// data->gfx.centre;
	/*while (ty > 240)
		ty -= 240;*/
	stretch = (data->gfx.height) / 240;
	while (y < data->gfx.height)
	{
		i = 0;
		while(i < stretch && tx < 720)
		{
			pixel_put(&data->gfx, x, y + i, data->gfx.texture[4].frame[0].pixels[tx + ty * 720]);
			i ++;//  data->gfx.scale;
		}
		y += i;
		ty++;
	}
}

void	draw_skybox(t_drown *data)
{
	int		x;
	int		tx;
	int		stretch;
	int		i;

	x = 0;
	tx = (int)roundf((720.f / (360.f * (float)DEGREES)) * data->player.dir);
	stretch = (data->gfx.width * data->gfx.scale) / 320;
	if (tx < 0)
		tx *= -1;
	while (x < data->gfx.width)
	{
		if (tx >= 720)
		tx -= 720;
		i = 0;
		while (i < stretch)
		{
			draw_skybox_collumn(data, x + i, tx);
			i++;
		}
		x += i;
		tx++;
	}
}


//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void		sdl_loop(t_drown *d)
{
	d->system.keyboard_state = SDL_GetKeyboardState(NULL);
	while (d->system.play_state == PLAY)
	{
	//	d->map.map[4][15][3] = '$';
	//	d->map.map[5][18][3] = 'Z';
		/*crouch(d);
		d->player.velocity.y -= GRAVITY;
		d->player.height += d->player.velocity.y * d->system.frame_time;
		if (d->player.height <= d->player.base_height + (d->map.map[(int)roundf(d->player.y / BITS)]
			[(int)roundf(d->player.x / BITS)][0] - '0') * 8)
		{
			d->player.height = d->player.base_height + (d->map.map[(int)roundf(d->player.y / BITS)]
			[(int)roundf(d->player.x / BITS)][0] - '0') * 8;
			d->player.velocity.y = 0;
			d->player.in_air = 0;
		}
		if (d->player.height > 514)
			d->player.height = 514;*/
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
		

		if (d->map.map[(int)roundf(d->player.y / 64)][(int)roundf(d->player.x / 64)][3] == 'Z') //&& d->player.height - d->player.base_height != d->player.altitude)
			d->system.ending_state = REGULAR_ENDING;

		if (d->system.frame_time < 16.6666f)			//OPTIMOI MINUT
		{
			SDL_Delay(16.6666f - d->system.frame_time);
		}
			draw_skybox(d);
			render(d);
			d->system.last_time = d->system.time;
		
	}
}
