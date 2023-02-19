/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_save_changes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:21:34 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/19 14:22:13 by aviholai         ###   ########.fr       */
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
