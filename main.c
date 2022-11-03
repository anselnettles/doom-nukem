/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/03 15:34:39 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libSDL2/include/SDL2/SDL.h"

#define WINDOW 480

int	main()
{
	write(1, "Crossroads of my programming life.", 34);
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	int				i;

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow("Game.", 0, 0, WINDOW, WINDOW, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	i = 200;
	while (i)
	{
		SDL_RenderDrawPoint(renderer, i, i);
		i--;
	}
	SDL_RenderPresent(renderer);
	while (1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}

