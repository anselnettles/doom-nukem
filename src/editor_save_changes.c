/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_changes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: tturto                                   #+#    #+#             */
/*   Updated: 2023/02/19 14:22:56 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Checks if 'S' was pressed.
    Return 1 on success, 0 on fail
*/
int	save_changes(t_gfx *gfx)
{
	if (gfx->event.type == SDL_KEYDOWN)
	{
		if (gfx->event.key.keysym.sym == SDLK_s)
			return (1);
	}
	return (0);
}
