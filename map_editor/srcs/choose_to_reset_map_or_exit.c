#include "../includes/map_editor.h"

//!!!  remove t_map *data. Used only for testing_print_map()
void    choose_to_reset_map_or_exit(t_editor *editor, t_editor_images *images, t_mouse *mouse, t_map *data)
{
    if (editor->event.button.button == SDL_BUTTON_RIGHT) //double executes now. Insert separately into img1-img2 & img3 functions?
    {
        printf("M2 was pressed\n");
        images->img_switch = 1;
        SDL_RenderClear(editor->renderer);
        SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x00, 0x00, 0x00);
        img1_to_gui(editor, mouse, images);
        SDL_RenderPresent(editor->renderer);
    }
    if (editor->event.type == SDL_KEYDOWN)   
    {
        testing_print_map(data, images);
        if (editor->event.key.keysym.sym == SDLK_ESCAPE)
            close_program(editor);
        // key presses
    }
}
