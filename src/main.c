/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/02 21:22:20 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Initializes the necessary player variables before rendering.
static int	initialize_player(t_drown *d)
{
	d->player.dir = PI;
	d->player.x = BITS * 2;
	d->player.y = BITS * 2;
	d->player.dx = cosf(PI);
	d->player.dy = sinf(PI);
	d->player.height = 32;
	d->player.altitude = 0;
	return (0);
}

//	Runs the "main menu" user interface.
//	Awaits the player's input and returns back to 'main()', branching
//	to "normal mode", "hard mode" and level editor.
static int	initialize_menu(t_gfx *gfx, t_system *system, SDL_Event *event)
{
	while (system->play_state == PLAY)
	{
		gfx_write(gfx, "PRESS 'Z' TO PLAY .. 'X' HARD MODE .. 'C' EDITOR");
		// editor_pix_put(gfx, gfx->width / 2, gfx->height / 2, 0x00EEEEEE);
		while (SDL_PollEvent(event))
		{
			if (event->type == SDL_QUIT)
				system->play_state = EXIT;
			if (event->type == SDL_KEYDOWN)
			{
				if (system->keyboard_state[SDL_SCANCODE_Z])
					return (0);
				else if (system->keyboard_state[SDL_SCANCODE_X])
				{
					//TURN ON HARD MODE.
					return (0);
				}
				else if (system->keyboard_state[SDL_SCANCODE_C])
					return (RUN_EDITOR);
				else if (system->keyboard_state[SDL_SCANCODE_ESCAPE])
					system->play_state = EXIT;
			}
		}
		SDL_UpdateWindowSurface(gfx->window);
	}
	return (0);
}

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
static int	initialize_media(t_drown *d)
{
//	printf("hexvalue is: %d\n", d->gfx.animation.frames[0].pixels[]);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > SDL_ERROR)
	{
		d->system.play_state = PLAY;
		d->gfx.scale = 2;
		d->gfx.width = (WIDTH * d->gfx.scale);
		d->gfx.height = (HEIGHT * d->gfx.scale);
		d->gfx.proj_dist = (d->gfx.width / 2) / tan(30 * DEGREES);
		d->gfx.centre = (d->gfx.height / 2);
		d->system.overlay_toggle = TRUE;
		d->system.filters = TRUE;
		d->system.keyboard_state = SDL_GetKeyboardState(NULL);
		d->gfx.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, d->gfx.width, d->gfx.height, SDL_WINDOW_SHOWN);
		d->gfx.screen = SDL_GetWindowSurface(d->gfx.window);
		if (d->gfx.window && d->gfx.screen != NULL)
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
	if (read_map("maps/bluehole.dn", &data) == ERROR)
		return (ERROR);
	if (initialize_media(&data) == ERROR)
		return (error(SDL_FAIL));
	if (initialize_menu(&data.gfx, &data.system, &data.event) == RUN_EDITOR)
	{
		if (map_editor("maps/bluehole.dn", &data) == ERROR)
			return (error(EDITOR_FAIL));
	}
	if (initialize_player(&data) == ERROR)
		return (error(PLAYER_FAIL));
	if (data.system.play_state == PLAY)
		if (render(&data) == ERROR)
			return (error(RENDER_FAIL));
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl_loop(&data);
	return (0);
}
