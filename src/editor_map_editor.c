/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_map_editor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 17:57:40 by tturto            #+#    #+#             */
/*   Updated: 2023/03/02 23:19:01 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void    initialize_editor(char *map_file, t_drown *data)
{
    clear_surface(data);
    set_image_limits(data);
    set_values_for_parameters(&data->editor.chars);
    if (validate_map(data) != 1)
        tt_errors("main: validate_map_temp() fail.");
}

/*
    Visualizes a three dimensional character array and allows
        the user to modify the X-values of the array (<array>[][][X]).
*/
int map_editor(char *map_file, t_drown *data)
{
    short int       quit;

    initialize_editor(map_file, data);
    
    //validate_outer_walls() will not be called here. It is called in the following locations: 
    // 1) main/read_map()
    // 2) main/map_editor/select_new_param_value(): row204 "if (... data->map.param_to_modify == 0)"
    if (validate_outer_walls(&data->map, &data->editor.images) != 1)
        close_program(&data->gfx);
    // is_element_bloated() is set in code directly after validate_map() call, not here
    if (is_element_bloated(&data->map, &data->editor.images) != 1)
        close_program(&data->gfx);
    
    draw_grid_of_squares(data);
    SDL_UpdateWindowSurface(data->gfx.window);
    quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&data->gfx.event))
        {
            if (data->gfx.event.type == SDL_QUIT)
                quit = 1;
            if (data->gfx.event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&data->editor.mouse.x, &data->editor.mouse.y);
            if (img1_img2_is_mouse_in_grid(data) == 1 && (data->editor.images.img_switch == 1
                || data->editor.images.img_switch == 2))
                img1_and_img2(data);
            if (img3_is_mouse_in_grid(data) == 1 && data->editor.images.img_switch == 3)
            {
                data->map.selection_index = data->map.selection_y;  
                select_new_param_value(data);
            }
            choose_to_reset_map_or_exit(data);
            if (data->gfx.event.type == SDL_KEYDOWN)
            {
                if (data->gfx.event.key.keysym.sym == SDLK_z)
                    quit = 1;
            }
            SDL_UpdateWindowSurface(data->gfx.window);
	    }
    }
    return (0);
}
