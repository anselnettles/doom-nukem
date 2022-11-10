/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 17:53:22 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	keyboard(t_rain *r)
{
	while (SDL_PollEvent(&r->graph.e))
	{
		if (r->graph.e.type == SDL_KEYDOWN)
		{
			if (r->graph.e.key.keysym.sym == ESC)
			{
				SDL_DestroyWindow(r->graph.win);
				SDL_Quit();
				exit(0);
			}
			if (r->graph.e.key.keysym.sym == NUMPAD_MINUS)
			{
				if (r->graph.scale == 1)
					r->graph.scale++;
				else if (r->graph.scale == 2)
					r->graph.scale--;
				r->graph.width = WIDTH * r->graph.scale;
				r->graph.height = HEIGHT * r->graph.scale;
				SDL_SetWindowSize(r->graph.win, r->graph.width,
						r->graph.height);
			}
		}
		render(r);
	}
}
