#include "../includes/map_editor.h"

void    img1_and_img2(t_editor *editor, t_map *data, t_mouse *mouse, t_editor_images *images)
{
    if (editor->event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (editor->event.button.button == SDL_BUTTON_LEFT && images->img_switch == 1)
        {
            printf("img1: map_x %d, map_y %d | switch to img2\n", data->map_x, data->map_y);
            SDL_RenderClear(editor->renderer);
            SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(editor, mouse, images); 
            img2_to_gui(editor, images);
            SDL_RenderPresent(editor->renderer);
            images->img_switch = 2;
        }
        else if (editor->event.button.button == SDL_BUTTON_LEFT && images->img_switch == 2)
        {
            SDL_RenderClear(editor->renderer);
            SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(editor, mouse, images); 
            img2_to_gui(editor, images);
            param_to_modify(data);
            img3_to_gui(editor, images, data);
            SDL_RenderPresent(editor->renderer);
            images->img_switch = 3;
            printf("img2: param_to_modify: %d | switch to img3\n", data->param_to_modify);
        }
   }
}
