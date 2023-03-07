/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_img1_and_img2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:19:47 by tturto            #+#    #+#             */
/*   Updated: 2023/03/03 17:21:05 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	img1_and_img2(t_drown *data)
{
	if (data->gfx.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->editor.images.img_switch == 1)
		{
			printf("img1: map_x %d, map_y %d | switch to img2\n", data->map.map_x, data->map.map_y); //remove at FINAL build
			clear_surface(data);
			draw_grid_of_squares(data);
			data->editor.images.img_switch = 2;
			draw_grid_of_squares(data);
			SDL_UpdateWindowSurface(data->gfx.window);
		}
		else if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->editor.images.img_switch == 2)
		{
			clear_surface(data);
			data->editor.images.img_switch = 1;
			draw_grid_of_squares(data);
			data->editor.images.img_switch = 2;
			draw_grid_of_squares(data);
			param_to_modify(&data->map);
			data->editor.images.img_switch = 3;
			draw_grid_of_squares(data);
			SDL_UpdateWindowSurface(data->gfx.window);
			printf("img2: param_to_modify: %d | switch to img3\n", data->map.param_to_modify); //remove at FINAL build
		}
	}
}
