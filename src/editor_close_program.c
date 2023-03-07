/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_close_program.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:24:58 by tturto            #+#    #+#             */
/*   Updated: 2023/03/03 16:25:48 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	!!! To enhance:	
		send t_drown *data here,not *gfx. (void)data. screen->NULL. free(map)
*/
void	close_program(t_gfx *gfx)
{
	SDL_DestroyWindow(gfx->window);
	gfx->window = NULL;
	(void)gfx;
	SDL_Quit();
	exit(-1);
}
