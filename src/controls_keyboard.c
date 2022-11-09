/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_keyboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:16:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/09 16:47:11 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	keyboard(t_graph *graph)
{
	while (SDL_PollEvent(&graph->e))
	{
		if (graph->e.type == SDL_KEYDOWN)
		{
			if (graph->e.key.keysym.sym == SDLK_ESCAPE)
			{
				SDL_DestroyWindow(graph->win);
				SDL_Quit();
				exit(0);
			}
		}
	}
}
