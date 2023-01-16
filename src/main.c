/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/16 11:54:29 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

//	Loads the texture files for walls from the 'textures' folder and
//	saves them to the 't_texture' structure's SDL_Surface file[].
static int	initialize_textures(t_rain *rain)
{
	rain->texture.file[0] = img_load("textures/bricks_med.png");
	rain->texture.file[1] = img_load("textures/bricks_dark.png");
	rain->texture.file[2] = img_load("textures/bricks_med2.png");
	rain->texture.file[3] = img_load("textures/bricks_lit.png");
	if (!(rain->texture.file[0]) || !(rain->texture.file[1])
		|| !(rain->texture.file[2]) || !(rain->texture.file[3]))
		return (ERROR);
	return (0);
}

//	Initializes the necessary player variables before rendering.
static int	initialize_player(t_rain *r)
{
	if (!(r->stage.start_x) || !(r->stage.start_y))
		return (ERROR);
	r->player.move_speed = MOVE_SPEED;
	r->player.pos_x = (float)(SQUARE_SIZE * (r->stage.start_x + 1)
			- (SQUARE_SIZE / 2.0));
	r->player.pos_y = (float)(SQUARE_SIZE * (r->stage.start_y + 1)
			- (SQUARE_SIZE / 2.0));
	r->player.pos_angle = 90;
	r->player.dir_x = (float)cos(deg_to_rad(r->player.pos_angle));
	r->player.dir_y = (float)-sin(deg_to_rad(r->player.pos_angle));
	return (0);
}

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
static int	initialize_media(t_graph *g)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > SDL_ERROR)
	{
		g->scale = SCALE;
		g->width = (WIDTH * g->scale);
		g->height = (HEIGHT * g->scale);
		g->scanline = FALSE;
		g->win = SDL_CreateWindow(TITLE, 0, 0, g->width, g->height, 0);
		g->surf = SDL_GetWindowSurface(g->win);
		if (g->win != NULL || g->surf != NULL)
		{
			g->map = PLAYER_MAP;
			g->cast.plane_dist = (double)(g->width / 2)
				/ tan(deg_to_rad(FOV / 2));
			g->cast.degrees_per_column = (double)g->width / (double)FOV;
			g->cast.degrees_per_ray = (double)FOV / (double)g->width;
			return (0);
		}
	}
	else
	{
		g->sdl_error_string = SDL_GetError();
		write(1, "SDL Error: ", 11);
		write(1, g->sdl_error_string, ft_strlen(g->sdl_error_string));
	}
	return (ERROR);
}

// Beginning of graphical function calls. Runs the graphical sequences in the
// order of: initialization, rendering, looping.
int	graphic_interface(t_rain *rain)
{
	if (initialize_media(&rain->graph) == ERROR)
		return (error(SDL_FAIL));
	if (initialize_player(rain) == ERROR)
		return (error(RENDER_FAIL));
	if (initialize_textures(rain) == ERROR)
		return (error(TEXTURE_FAIL));
	if (render(rain) == ERROR)
		return (error(RENDER_FAIL));
	sdl_loop(rain);
	return (0);
}

// Begin of program. Run the binary with no arguments to launch the game.
// Run the binary with a single argument to launch the level editor.

int	main(int argc, char **argv)
{
	t_rain	rain;

	ft_bzero(&rain, sizeof(t_rain));
	rain.system.user_request = argc;
	rain.editor.file = argv[1];
	if (rain.system.user_request == RUN_GAME)
	{
		if (graphic_interface(&rain) == ERROR)
			return (ERROR);
	}
	else if (rain.system.user_request == RUN_LEVEL_EDITOR)
	{
		if (read_file(&rain) == ERROR)
			return (ERROR);
	}
	else
		return (error(BAD_ARGS));
	return (0);
}
