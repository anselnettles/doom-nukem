/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/04 17:39:09 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdio.h>

/*static int	practice(void)
{
	SDL_Event		event;
	SDL_Renderer	*renderer;
	SDL_Window		*win;
	int				i;

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_CreateWindow(TITLE, 0, 0, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderClear(renderer);
	i = 200;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	while (i)
	{
		SDL_RenderDrawPoint(renderer, i, i);
		i--;
	}
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	while (1)
	{
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break ;
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}*/

// Begin of program. Run the binary with no arguments to launch the game.
// Run the binary with a single argument to launch the level editor.

int	main(int argc, char **argv)
{
	t_system	s;

	s.user_request = 0;
	if (argc == 1)
	{
		s.user_request = RUN_GAME;
		printf("run game. ");
	}
	else if (argc == 2)
	{
		s.user_request = RUN_LEVEL_EDITOR;
		printf("run editor. %s", argv[1]);
	}
	else
		return (error(BAD_ARGS));
	return (0);
}
