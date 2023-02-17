/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/17 18:53:31 by aviholai         ###   ########.fr       */
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

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
static int	initialize_media(t_drown *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_EVERYTHING) > SDL_ERROR)
	{
		d->gfx.scale = 1;
		d->gfx.width = (WIDTH * d->gfx.scale);
		d->gfx.height = (HEIGHT * d->gfx.scale);
		d->hg = d->gfx.height / 2;
		d->system.overlay_toggle = TRUE;
		d->system.play_state = PLAY;
		d->gfx.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, d->gfx.width,
				d->gfx.height, SDL_WINDOW_SHOWN);
		d->gfx.dop = d->gfx.width / 2 / tan(30 * DEGREES);
		d->gfx.renderer = SDL_CreateRenderer(d->gfx.window, -1, SDL_RENDERER_ACCELERATED); //To be removed. Bring gfx.screen back.
		if (d->gfx.window != NULL || d->gfx.renderer != NULL)
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

int	main(int argc, char **argv)
{
	t_drown	data;

	ft_bzero(&data, sizeof(t_drown));
	if (argc != 2)
		return (error(NO_FILE));
	if (initialize_media(&data) == ERROR)
		return (error(SDL_FAIL));
	map_editor(argv[1], &data);
									SDL_DestroyRenderer(data.gfx.renderer);		//To be removed in favor of 'pixel_put()'.
									data.gfx.renderer = NULL;
									data.gfx.screen = SDL_GetWindowSurface(data.gfx.window);
										if (data.gfx.screen == NULL)
											return (0);
	if (initialize_player(&data) == ERROR)
		return (error(PLAYER_FAIL));
	if (render(&data) == ERROR)
		return (error(RENDER_FAIL));
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl_loop(&data);
	return (0);
}
