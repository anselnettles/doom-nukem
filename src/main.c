/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 17:42:17 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Loads the texture files for walls from the 'textures' folder and
//	saves them to the 't_texture' structure's SDL_Surface file[].
static int	initialize_textures(t_drown *drown)
{
	drown->graph.texture[0] = img_load("textures/bricks_med.png");
	drown->graph.texture[1] = img_load("textures/bricks_dark.png");
	drown->graph.texture[2] = img_load("textures/bricks_med2.png");
	drown->graph.texture[3] = img_load("textures/bricks_lit.png");
	if (!(drown->graph.texture[0]) || !(drown->graph.texture[1])
		|| !(drown->graph.texture[2]) || !(drown->graph.texture[3]))
		return (ERROR);
	return (0);
}

//	Initializes the necessary player variables before rendering.
static int	initialize_player(t_drown *d)
{
	if (!(d->editor.start_x) || !(d->editor.start_y))
		return (ERROR);
	d->player.move_speed = MOVE_SPEED;
	d->player.pos_x = (float)(SQUARE_SIZE * (d->editor.start_x + 1)
			- (SQUARE_SIZE / 2.0));
	d->player.pos_y = (float)(SQUARE_SIZE * (d->editor.start_y + 1)
			- (SQUARE_SIZE / 2.0));
	d->player.pos_angle = 90;
	d->player.dir_x = (float)cos(deg_to_rad(d->player.pos_angle));
	d->player.dir_y = (float)-sin(deg_to_rad(d->player.pos_angle));
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
int	graphic_interface(t_drown *drown)
{
	if (initialize_media(&drown->graph) == ERROR)
		return (error(SDL_FAIL));
	if (initialize_player(drown) == ERROR)
		return (error(PLAYER_FAIL));
	if (initialize_textures(drown) == ERROR)
		return (error(TEXTURE_FAIL));
	if (render(drown) == ERROR)
		return (error(RENDER_FAIL));
	sdl_loop(drown);
	return (0);
}

// Begin of program. Run the binary with no arguments to launch the game.
// Run the binary with a single argument to launch the level editor.

int	main(int argc, char **argv)
{
	t_drown	drown;

	ft_bzero(&drown, sizeof(t_drown));
	drown.system.user_request = argc;
	(void)argv;
	//rain.editor.file = argv[1];
	if (drown.system.user_request == RUN_GAME)
	{
	//	rain.editor.file = "maps/alleyway_maze.dn";
	//	if (!(rain.editor.file))
	//		return (error(OPEN_FAIL));
	//	if (read_file(&rain) == ERROR)
	//		return (ERROR);
	}
	else
		return (error(BAD_ARGS));
	return (0);
}
