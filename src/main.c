/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:56:29 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/26 16:46:20 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	main(int ac, char **av)
{
	t_main	data;

	if (ac != 2)
		ft_exit("invalid arguments");
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to initialize SDL! SDL Error: %s\n", SDL_GetError());
		return (0);
	}
	read_map(av[1], &data.map);
	init_player(&data.player);
	data.option = PLAY;
	data.thread = 1;
	data.height = 0;
	data.window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (init_sdl(data.window, data.screen) == 0)
		exit(-1);
	render_thread(&data);
	draw_map(&data);
	SDL_UpdateWindowSurface(data.window);
	SDL_SetRelativeMouseMode(data.cursor);
	while (data.option != EXIT)
	{
		while (SDL_PollEvent(&data.event) != 0)
		{
			if (data.event.type == SDL_QUIT)
				data.option = EXIT;
			else if (data.event.type == SDL_KEYDOWN)
				deal_key(data.event.key.keysym.sym, &data);
			else if (data.event.type == SDL_MOUSEMOTION)
				deal_mouse(&data);
		}
	}
	return (0);
}
