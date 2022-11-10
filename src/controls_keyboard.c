/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 17:26:37 by aviholai         ###   ########.fr       */
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
				if (r->graph.scaler == 1)
					r->graph.scaler++;
				else if (r->graph.scaler == 2)
					r->graph.scaler--;
				r->graph.width = WIDTH * r->graph.scaler;
				r->graph.height = HEIGHT * r->graph.scaler;
				SDL_SetWindowSize(r->graph.win, r->graph.width,
						r->graph.height);
			}
		}
		render(r);
	}
}
