/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:25:23 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/26 16:27:36 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
