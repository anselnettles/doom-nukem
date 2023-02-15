#include "../../src/drowning.h"

int map_editor(char *map_file, t_map *map)
{
    t_gfx           gfx;    //former t_editor editor
    t_mouse         mouse;  // -
    t_editor_images images; // -
    t_character     chars;  // -
    short int       quit;

    initialization(&images, map, &chars, map_file, &gfx);
    if (init(&gfx) != 1)
    {
        tt_errors("main: init() fail");
        close_program(&gfx);
    }
    img1_to_gui(&gfx, &mouse, &images);
    //consider inserting SetRenderDrawColor & RenderPresent to a single function
    SDL_SetRenderDrawColor(gfx.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderPresent(gfx.renderer);  
    quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&editor.event))
        {
            if (gfx.event.type == SDL_QUIT)
                quit = 1;
            if (gfx.event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&mouse.x, &mouse.y);
            if (img1_img2_is_mouse_in_grid(&mouse, map, &images) == 1 && (images.img_switch == 1 || images.img_switch == 2))
                img1_and_img2(&gfx, map, &mouse, &images);
            if (img3_is_mouse_in_grid(&mouse, map, &images) == 1 && images.img_switch == 3)
            {
                //data->selection_index can be set in this manner due to grid of img3 is pre-defined as a single column
                map->selection_index = map->selection_y;  
                printf("selection_index: %d\n", map->selection_index);
                select_new_param_value(&gfx, map, &chars);
            }
            if (save_changes(&gfx) == 1)
            {
                if (overwrite_map_file(data, &images) == 1)
                    printf("default.txt was overwritten\n");
                else
                    printf("no overwrite\n");
            }
            choose_to_reset_map_or_exit(&editor, &images, &mouse, data);
        }
    }
    return (0);
}
