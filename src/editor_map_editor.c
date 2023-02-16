#include "drowning.h"

int map_editor(char *map_file, t_drown *data)
{
    short int       quit;

    initialization(data, map_file);
    /*if (init(&data->gfx) != 1)    //remove
    {
        tt_errors("main: init() fail");
        close_program(&data->gfx);
    }*/
    img1_to_gui(data);
    SDL_SetRenderDrawColor(data->gfx.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderPresent(data->gfx.renderer);  
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
        }
    }
    return (0);
}
