/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:05:39 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/07 19:17:44 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	The graphical render order: Fill in black, draw the 3D space, draw the
//	array map in the window corner, update the window.

int	render(t_drown *data)
{
	render_thread(data);
	if (data->system.overlay_toggle == TRUE)
		if (render_overlay(data) == ERROR)
			return (error(OVERLAY_ERROR));
	if (SDL_UpdateWindowSurface(data->gfx.window) == ERROR)
		return (ERROR);
	return (0);
}
