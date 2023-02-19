/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_img1_and_img2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: tturto                                   #+#    #+#             */
/*   Updated: 2023/02/19 13:45:26 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	img1_and_img2(t_drown *data)
{
	if (data->gfx.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT && data->editor.images.img_switch == 1)
		{
			printf("img1: map_x %d, map_y %d | switch to img2\n", data->map.map_x, data->map.map_y);
			SDL_RenderClear(data->gfx.renderer);
			SDL_SetRenderDrawColor(data->gfx.renderer, 0x00, 0x00, 0x00, 0x00);
			img1_to_gui(data);
			img2_to_gui(data);
			SDL_RenderPresent(data->gfx.renderer);
			data->editor.images.img_switch = 2;
		}
		else if (data->gfx.event.button.button == SDL_BUTTON_LEFT && data->editor.images.img_switch == 2)
		{
			SDL_RenderClear(data->gfx.renderer);
			SDL_SetRenderDrawColor(data->gfx.renderer, 0x00, 0x00, 0x00, 0x00);
			img1_to_gui(data);
			img2_to_gui(data);
			param_to_modify(&data->map);
			img3_to_gui(data);
			SDL_RenderPresent(data->gfx.renderer);
			data->editor.images.img_switch = 3;
			printf("img2: param_to_modify: %d | switch to img3\n", data->map.param_to_modify);
		}
	}
}
