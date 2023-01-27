/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 13:56:29 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/27 15:07:38 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int	main(int ac, char **av)
{
	t_main	data;

	if (ac != 2)
		ft_exit("invalid arguments");
	read_map(av[1], &data.map);
	init_values(&data);
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
		clear_screen(&data);
		render_thread(&data);
		draw_map(&data);
		SDL_UpdateWindowSurface(data.window);
	}
	return (0);
}
