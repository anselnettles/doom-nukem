#include "drowning.h"

static int	initialize_editor(t_drown *data)
{
	set_image_limits(&data->editor.images);
	set_values_for_parameters(&data->editor.chars);
	create_map_temp(data);
	copy_map_to_map_temp(data);
	if (validate_map_temp(data) != 1)
		return (ERROR);
	return (0);
}

int map_editor(t_drown *data)
{
		SDL_FillRect(data->gfx.screen, NULL, 0);	//to be removed.
		SDL_UpdateWindowSurface(data->gfx.window);	//to be removed.
	short int	quit;
	if (initialize_editor(data) == ERROR)
		return (ERROR);
	img1_to_gui(data);
	//SDL_SetRenderDrawColor(data->gfx.renderer, 0x00, 0x00, 0x00, 0x00);
	//SDL_RenderPresent(data->gfx.renderer);  
	quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&data->gfx.event))
        {
            if (data->gfx.event.type == SDL_QUIT)
                quit = 1;
            if (data->gfx.event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&data->editor.mouse.x, &data->editor.mouse.y);
            if (img1_img2_is_mouse_in_grid(data) == 1 && (data->editor.images.img_switch == 1 || data->editor.images.img_switch == 2))
                img1_and_img2(data);
            if (img3_is_mouse_in_grid(data) == 1 && data->editor.images.img_switch == 3)
            {
                //data->selection_index can be set in this manner due to grid of img3 is pre-defined as a single column
                data->map.selection_index = data->map.selection_y;  
                printf("selection_index: %d\n", data->map.selection_index);
                select_new_param_value(data);
            }
            if (save_changes(&data->gfx) == 1)
            {
                if (overwrite_map_file(&data->map, &data->editor.images) == 1)
                    write(1, "default.txt was overwritten\n", 28);
                else
                    write(1, "no overwrite\n", 13);
            }
            choose_to_reset_map_or_exit(data);
	    if (data->gfx.event.type == SDL_KEYDOWN)
	    {
		    if (data->gfx.event.key.keysym.sym == SDLK_z
				    || data->gfx.event.key.keysym.sym == SDLK_x)
			    quit = 1;
	    }
	}
    }
    return (0);
}
