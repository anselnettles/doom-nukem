#include "../includes/map_editor.h"

int map_editor(char *map_file, t_map *data)
{
    t_editor        editor;
    t_mouse         mouse;
    t_editor_images images;
    t_character     chars;
    short int       quit;

    initialization(&images, data, &chars, map_file, &editor);
    if (init(&editor) != 1)
    {
        tt_errors("main: init() fail");
        close_program(&editor);
    }
    img1_to_gui(&editor, &mouse, &images);
    //consider inserting SetRenderDrawColor & RenderPresent to a single function
    SDL_SetRenderDrawColor(editor.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderPresent(editor.renderer);  
    quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&editor.event))
        {
            if (editor.event.type == SDL_QUIT)
                quit = 1;
            if (editor.event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&mouse.x, &mouse.y);
            if (img1_img2_is_mouse_in_grid(&mouse, data, &images) == 1 && (images.img_switch == 1 || images.img_switch == 2))
                img1_and_img2(&editor, data, &mouse, &images);
            if (img3_is_mouse_in_grid(&mouse, data, &images) == 1 && images.img_switch == 3)
            {
                //data->selection_index can be set in this manner due to grid of img3 is pre-defined as a single column
                data->selection_index = data->selection_y;  
                printf("selection_index: %d\n", data->selection_index);
                select_new_param_value(&editor, data, &chars);
            }
            if (save_changes(&editor) == 1)
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
