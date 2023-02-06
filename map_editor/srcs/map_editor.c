#include "../includes/map_editor.h"

int map_editor(char *map_file, t_map *data)
{
    t_editor        editor;
    t_mouse         mouse;
    t_editor_images images;
    t_character     chars;
    short int       quit;

    //create a function "initialize_data()" here, and insert the below 5 functions into it
    set_image_limits(&images);
    set_values_for_parameters(&chars);
    read_map(map_file, data, &images);
    create_map_temp(data, &images);
    copy_map_to_map_temp(data, &images);
    // testing_print_map(data, &images);
    if (init(&editor) != 1)
    {
        tt_errors("main: init() fail");
        close_program(&editor);
    }
    img1_to_gui(&editor, &mouse, &images); 
    SDL_SetRenderDrawColor(editor.renderer, 0x00, 0x00, 0x00, 0x00); //consider one-lining SetRenderDrawColor & RenderPresent
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
            if (get_m1_pressed_map_element(&mouse, data, &images) == 1 && (images.img_switch == 1 || images.img_switch == 2))
                img1_and_img2(&editor, data, &mouse, &images);
            if (get_m1_pressed_img3_grid_element(&mouse, data, &images) == 1 && images.img_switch == 3)
            {
                data->selection_index = data->selection_y;  //note, this is valid due to grid3 being pre-defined as a column
                printf("selection_index: %d\n", data->selection_index);
                select_new_param_value(&editor, data, &chars, &images);
            }
            choose_to_reset_map_or_exit(&editor, &images, &mouse, data);
        }
    }
    return (0);
}
