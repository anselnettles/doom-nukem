/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 21:05:58 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Loads the texture files for walls from the 'textures' folder and
//	saves them to the 't_texture' structure's SDL_Surface file[].
static int	initialize_textures(t_drown *drown)
{
	(void)drown;
//	drown->graph.texture[0] = img_load("textures/bricks_med.png");
//	drown->graph.texture[1] = img_load("textures/bricks_dark.png");
//	drown->graph.texture[2] = img_load("textures/bricks_med2.png");
//	drown->graph.texture[3] = img_load("textures/bricks_lit.png");
//	if (!(drown->graph.texture[0]) || !(drown->graph.texture[1])
//		|| !(drown->graph.texture[2]) || !(drown->graph.texture[3]))
//		return (ERROR);
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


	//Dofidog:
	d->player.dir = PI;
	d->player.x = BITS * 2;
	d->player.y = BITS * 2;
	d->player.dx = cosf(PI);
	d->player.dy = sinf(PI);
	d->player.height = 32;
	return (0);
}

//	Initializes the SDL (Simple DirectMedia Layer) library functions and sets
//	all the necessary variables for graphical rendering.
static int	initialize_media(t_drown *d)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) > SDL_ERROR)
	{
		d->graph.scale = SCALE;
		d->graph.width = (WIDTH * d->graph.scale);
		d->graph.height = (HEIGHT * d->graph.scale);
		d->graph.scanline = FALSE;
		//g->win = SDL_CreateWindow(TITLE, 0, 0, g->width, g->height, 0);
		//g->surf = SDL_GetWindowSurface(g->win);

		//Dofidog:
		d->option = PLAY;
		d->thread = 1;
		d->hg = 0; //What exactly is Dofidog's data->height?
		d->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, d->graph.width, d->graph.height, SDL_WINDOW_SHOWN);

		d->screen = SDL_GetWindowSurface(d->window);
		//if (init_sdl(data->window, data->screen) == 0)
		//	exit(-1);

		if (d->window != NULL || d->screen != NULL)
		{
		//	g->map = PLAYER_MAP;
		//	g->cast.plane_dist = (double)(g->width / 2)
		//		/ tan(deg_to_rad(FOV / 2));
		//	g->cast.degrees_per_column = (double)g->width / (double)FOV;
		//	g->cast.degrees_per_ray = (double)FOV / (double)g->width;
			return (0);
		}
	}
	else
	{
		d->graph.sdl_error_string = SDL_GetError();
		write(1, "SDL Error: ", 11);
		write(1, d->graph.sdl_error_string, ft_strlen(d->graph.sdl_error_string));
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
	read_map("maps/testfile.dn", &data.map);
	if (initialize_player(&data) == ERROR)
		return (error(PLAYER_FAIL));
	if (initialize_textures(&data) == ERROR)
		return (error(TEXTURE_FAIL));
	if (render(&data) == ERROR)
		return (error(RENDER_FAIL));
	SDL_SetRelativeMouseMode(data.cursor);
	sdl_loop(&data);
	return (0);
}
