/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:57:40 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 18:25:43 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	initialize_editor(char *map_file, t_drown *data)
{
	data->editor.rules.quit = 0;
	data->editor.rules.valid = 1;
	clear_surface(data);
	set_image_limits(data);
	set_values_for_parameters(&data->editor.chars);
	if (validate_map(data) != 1)
		exit (-1);
	draw_grid_of_squares(data);
	SDL_UpdateWindowSurface(data->gfx.window);
}

static void	img_render(t_drown *data)
{
	if (img1_img2_is_mouse_in_grid(data) == 1
		&& (data->editor.images.img_switch == 1
			|| data->editor.images.img_switch == 2))
		img1_img2_img3(data);
	if (img3_is_mouse_in_grid(data) == 1 && data->editor.images.img_switch == 3)
	{
		data->map.selection_index = data->map.selection_y;
		select_new_param_value(data);
		if (is_new_map_valid(&data->map, &data->editor.images) != 1)
			data->editor.rules.valid = 0;
		else
			data->editor.rules.valid = 1;
	}	
}

/*
    Visualizes a three dimensional character array and allows
        the user to modify the X-values of the array (<array>[][][X]).
*/
int	map_editor(char *map_file, t_drown *data)
{
	initialize_editor(map_file, data);
	while (data->editor.rules.quit == 0)
	{
		while (SDL_PollEvent(&data->gfx.event))
		{
			if (data->gfx.event.type == SDL_QUIT)
				data->editor.rules.quit = 1;
			if (data->gfx.event.type == SDL_MOUSEMOTION)
				SDL_GetMouseState(&data->editor.mouse.x, &data->editor.mouse.y);
			img_render(data);
			choose_to_reset_map_or_exit(data);
			if (data->gfx.event.type == SDL_KEYDOWN
				&& data->editor.rules.valid == 1)
			{
				if (data->gfx.event.key.keysym.sym == SDLK_z)
					data->editor.rules.quit = 1;
			}
			SDL_UpdateWindowSurface(data->gfx.window);
		}
	}
	return (0);
}
