/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/09 12:28:57 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int	initialize_textures(t_drown *d)
{
	sprite_right_arm(d);
	return (0);
}

//	Initializes the necessary player variables before rendering.
static int	initialize_player(t_drown *d)
{
	//if (!(d->editor.start_x) || !(d->editor.start_y))
	//	return (ERROR);
	//d->player.move_speed = MOVE_SPEED;
	//d->player.pos_x = (float)(SQUARE_SIZE * (d->editor.start_x + 1)
	//		- (SQUARE_SIZE / 2.0));
	//d->player.pos_y = (float)(SQUARE_SIZE * (d->editor.start_y + 1)
	//		- (SQUARE_SIZE / 2.0));
	//d->player.pos_angle = 90;
	//d->player.dir_x = (float)cos(deg_to_rad(d->player.pos_angle));
	//d->player.dir_y = (float)-sin(deg_to_rad(d->player.pos_angle));
	d->player.dir = PI;
	d->player.x = BITS * 2;
	d->player.y = BITS * 2;
	d->player.dx = cosf(PI);
	d->player.dy = sinf(PI);
	d->player.height = 32;
	d->player.altitude = 0;
	return (0);
}

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
static int	initialize_media(t_drown *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > SDL_ERROR)
	{
		d->gfx.scale = 1;
		d->gfx.width = (WIDTH * d->gfx.scale);
		d->gfx.height = (HEIGHT * d->gfx.scale);
		d->hg = d->gfx.height / 2;
		d->gfx.overlay_toggle = TRUE;
		d->system.play_state = PLAY;
		d->gfx.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, d->gfx.width,
				d->gfx.height, SDL_WINDOW_SHOWN);
		d->gfx.screen = SDL_GetWindowSurface(d->gfx.window);
		d->gfx.dop = d->gfx.width / 2 / tan(30 * DEGREES);
		if (d->gfx.window != NULL || d->gfx.screen != NULL)
			return (0);
	}
	else
	{
		d->gfx.sdl_error_string = SDL_GetError();
		write(1, "SDL Error: ", 11);
		write(1, d->gfx.sdl_error_string, ft_strlen(d->gfx.sdl_error_string));
	}
	return (ERROR);
}

// Begin of program. Run the binary with no arguments to launch the software
// and go into the process of initialization.

int	main(void)
{
	t_drown	data;

	ft_bzero(&data, sizeof(t_drown));
	if (initialize_media(&data) == ERROR)
		return (error(SDL_FAIL));
	read_map("maps/numbers.dn", &data.map);
	if (initialize_player(&data) == ERROR)
		return (error(PLAYER_FAIL));
	if (initialize_textures(&data) == ERROR)
		return (error(TEXTURE_FAIL));
	if (render(&data) == ERROR)
		return (error(RENDER_FAIL));
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl_loop(&data);
	return (0);
}
