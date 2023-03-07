/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_choose_to_reset_map_or_exit.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:14:40 by tturto            #+#    #+#             */
/*   Updated: 2023/03/03 16:14:56 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	choose_to_reset_map_or_exit(t_drown *data)
{
	if (data->gfx.event.button.button == SDL_BUTTON_RIGHT)
	{
		clear_surface(data);
		data->editor.images.img_switch = 1;
		draw_grid_of_squares(data);
		SDL_UpdateWindowSurface(data->gfx.window);
	}
	if (data->gfx.event.type == SDL_KEYDOWN)
	{
		if (data->gfx.event.key.keysym.sym == SDLK_ESCAPE)
			close_program(&data->gfx);
	}
}
