#include "drowning.h"

//!!!  remove t_map *data. Used only for testing_print_map()
void    choose_to_reset_map_or_exit(t_drown *data)
{
    if (data->gfx.event.button.button == SDL_BUTTON_RIGHT) //double executes now. Insert separately into img1-img2 & img3 functions?
    {
        printf("M2 was pressed\n");
        data->editor.images.img_switch = 1;
        SDL_RenderClear(data->gfx.renderer);
        SDL_SetRenderDrawColor(data->gfx.renderer, 0x00, 0x00, 0x00, 0x00);
        img1_to_gui(data);
        SDL_RenderPresent(data->gfx.renderer);
    }
    if (data->gfx.event.type == SDL_KEYDOWN)   
    {
        // testing_print_map(data, images);
        if (data->gfx.event.key.keysym.sym == SDLK_ESCAPE)
            close_program(&data->gfx);
        // key presses
    }
}
