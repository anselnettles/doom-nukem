/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_img1_img2_img3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:19:47 by tturto            #+#    #+#             */
/*   Updated: 2023/03/13 15:45:51 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	img2_img3(t_drown *data)
{
	clear_surface(data);
	data->editor.images.img_switch = 1;
	draw_grid_of_squares(data);
	data->editor.images.img_switch = 2;
	draw_grid_of_squares(data);
	img2_texts(data);
	param_to_modify(&data->map);
	data->editor.images.img_switch = 3;
	draw_grid_of_squares(data);
	img3_texts(data, data->map.param_to_modify);
	SDL_UpdateWindowSurface(data->gfx.window);
}

static void	img1_img2(t_drown *data)
{
	clear_surface(data);
	draw_grid_of_squares(data);
	data->editor.images.img_switch = 2;
	draw_grid_of_squares(data);
	img2_texts(data);
	SDL_UpdateWindowSurface(data->gfx.window);
}

void	img1_img2_img3(t_drown *data)
{
	if (data->gfx.event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->editor.images.img_switch == 1)
		{
			img1_img2(data);
		}
		else if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->editor.images.img_switch == 2)
		{
			img2_img3(data);
		}
		else if (data->gfx.event.button.button == SDL_BUTTON_LEFT
			&& data->editor.images.img_switch == 3)
		{
			img2_img3(data);
		}
	}
}
