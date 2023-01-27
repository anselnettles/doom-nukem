/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:25:23 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/27 16:29:30 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	init_sdl(SDL_Window *window, SDL_Surface *screen)
{
	if (window == NULL)
		printf("Window couldnt be created! SDL_Error: %s\n", SDL_GetError());
	else
	{
		if (!(screen = SDL_GetWindowSurface(window)))
			printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
		SDL_FillRect(screen, NULL,
			SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	}
	SDL_UpdateWindowSurface(window);
	return (1);
}

void	init_player(t_player *player)
{
	player->dir = PI;
	player->x = BITS * 2;
	player->y = BITS * 2;
	player->dx = cosf(PI);
	player->dy = sinf(PI);
	player->height = 32;
}

void	init_data(t_drown *data)
{
	data->option = PLAY;
	data->thread = 1;
	data->height = 0;
	data->window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (init_sdl(data->window, data->screen) == 0)
		exit(-1);
}
void	init_values(t_drown *data)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
		exit(-1);
	}
	init_player(&data->player);
	init_data(data);

}
