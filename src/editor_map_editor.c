/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:57:40 by tturto            #+#    #+#             */
/*   Updated: 2023/03/07 18:57:07 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void    initialize_editor(char *map_file, t_drown *data)
{
    data->editor.rules.quit = 0;
    data->editor.rules.acceptable = 1;
    clear_surface(data);
    set_image_limits(data);
    set_values_for_parameters(&data->editor.chars);
    if (validate_map(data) != 1)
        tt_errors("main: validate_map_temp() fail.");
    draw_grid_of_squares(data);
    SDL_UpdateWindowSurface(data->gfx.window);
}

/*
    Visualizes a three dimensional character array and allows
        the user to modify the X-values of the array (<array>[][][X]).
*/
int map_editor(char *map_file, t_drown *data)
{
    // is_element_bloated() is set in code directly after validate_map() call, not here
    // if (is_element_bloated(&data->map, &data->editor.images) != 1)
    // {
    //     write(1, "bloated element\n", 16);
    //     //close_program(&data->gfx);
    // }
    
    initialize_editor(map_file, data);
    while (data->editor.rules.quit == 0)
    {
        while (SDL_PollEvent(&data->gfx.event))
        {
            editor_test_write(&data->gfx, "ABCDEF", data->gfx.width / 2, data->gfx.height / 2);
            if (data->gfx.event.type == SDL_QUIT)
                data->editor.rules.quit = 1;
            if (data->gfx.event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&data->editor.mouse.x, &data->editor.mouse.y);
            if (img1_img2_is_mouse_in_grid(data) == 1 && (data->editor.images.img_switch == 1
                || data->editor.images.img_switch == 2))
                img1_and_img2(data);
            if (img3_is_mouse_in_grid(data) == 1 && data->editor.images.img_switch == 3)
            {
                data->map.selection_index = data->map.selection_y;  
                select_new_param_value(data);
                if (validate_outer_walls(&data->map, &data->editor.images) != 1)
                    data->editor.rules.acceptable = 0;
                else
                    data->editor.rules.acceptable = 1;
            }
            choose_to_reset_map_or_exit(data);
            if (data->gfx.event.type == SDL_KEYDOWN && data->editor.rules.acceptable == 1)
            {
                if (data->gfx.event.key.keysym.sym == SDLK_z)
                    data->editor.rules.quit = 1;
            }
            SDL_UpdateWindowSurface(data->gfx.window);
	    }
    }
    return (0);
}
