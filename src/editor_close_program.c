/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_close_program.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/02/28 18:17:06 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	close_program(t_gfx *gfx)	//send t_drown *data here instead of *gfx. (void)data. screen->NULL. free(map)
{
	SDL_DestroyWindow(gfx->window);
	gfx->window = NULL;
	(void)gfx;
	SDL_Quit();
	exit(-1);
}
