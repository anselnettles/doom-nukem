/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 12:31:27 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Initializes the necessary player variables before rendering.
static int	initialize_player(t_drown *d)
{
	d->player.dir = PI;
	d->player.x = get_player_start(&d->map, &d->editor.images, 'x');
	d->player.y = get_player_start(&d->map, &d->editor.images, 'y');
	d->player.dx = cosf(PI);
	d->player.dy = sinf(PI);
	d->player.height = 512;
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
		menu_string(gfx, gfx->scale);
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
					system->hard_mode = TRUE;
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

static void	initialize_audio(t_drown *d)
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	d->audio.main_menu = Mix_LoadMUS("src/audio/bgm_grave_menu.ogg");
	d->audio.bluehole = Mix_LoadMUS("src/audio/bgm_grave_theme.ogg");
	d->audio.timer_hit = Mix_LoadWAV("src/audio/se_timer_hit.ogg");
	d->audio.inhale = Mix_LoadWAV("src/audio/se_inhale.ogg");
	Mix_PlayMusic(d->audio.main_menu, 0);
}

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
static int	initialize_media(t_drown *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO) > SDL_ERROR)
	{
		d->system.play_state = PLAY;
		d->gfx.scale = 2;
		d->gfx.width = (WIDTH * d->gfx.scale);
		d->gfx.height = (HEIGHT * d->gfx.scale);
		d->gfx.proj_dist = (d->gfx.width / 2) / tan(30 * DEGREES);
		d->gfx.centre = (d->gfx.height / 2);
		d->system.overlay_toggle = TRUE;
		d->system.filters = TRUE;
		d->system.transition = TRUE;
		d->system.keyboard_state = SDL_GetKeyboardState(NULL);
		d->gfx.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
				0, d->gfx.width, d->gfx.height, SDL_WINDOW_SHOWN);
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
	initialize_audio(&data);
	if (initialize_menu(&data.gfx, &data.system, &data.event) == RUN_EDITOR)
		if (map_editor("maps/bluehole.dn", &data) == ERROR)
			return (error(EDITOR_FAIL));
	if (initialize_player(&data) == ERROR)
		return (error(PLAYER_FAIL));
	if (data.system.play_state == PLAY)
	{
		Mix_PlayMusic(data.audio.bluehole, -1);
		Mix_VolumeMusic(50);
		if (render(&data) == ERROR)
			return (error(RENDER_FAIL));
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	sdl_loop(&data);
	return (0);
}
