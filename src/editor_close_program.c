/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_close_program.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: tturto                                   #+#    #+#             */
/*   Updated: 2023/02/19 13:43:18 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	close_program(t_gfx *gfx)
{
	//free map or map_temp
	SDL_DestroyRenderer(gfx->renderer);
	gfx->renderer = NULL;
	SDL_DestroyWindow(gfx->window);
	gfx->window = NULL;
	(void)gfx;
	SDL_Quit();
	exit(-1);
}
