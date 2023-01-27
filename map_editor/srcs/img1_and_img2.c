#include "../includes/map_editor.h"

void    img1_and_img2(t_editor *editor, t_map *dimensions, t_mouse *mouse, t_editor_images *lim)
{
    if (editor->event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (editor->event.button.button == SDL_BUTTON_LEFT && lim->img_switch == 1)
        {
            printf("A grid was clicked. img_switch: %d\n", lim->img_switch);
            SDL_RenderClear(editor->renderer);
            SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(editor, mouse, lim); 
            img2_to_gui(editor, lim);
            SDL_RenderPresent(editor->renderer);
            printf("map_x %d | map_y %d\n", lim->map_x, lim->map_y);
            lim->img_switch = 2;
            dimensions->x_to_modify = lim->map_x;
            dimensions->y_to_modify = lim->map_y;
            printf("Operations done. img_switch: %d\n", lim->img_switch);
        }
        else if (editor->event.button.button == SDL_BUTTON_LEFT && lim->img_switch == 2)
        {
            printf("A grid was clicked. img_switch: %d\n", lim->img_switch);
            SDL_RenderClear(editor->renderer);
            SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(editor, mouse, lim); 
            img2_to_gui(editor, lim);
            printf("map_x %d | map_y %d\n", lim->map_x, lim->map_y);
            dimensions->param_x_to_modify = lim->map_x;
            dimensions->param_y_to_modify = lim->map_y;
            param_to_modify(dimensions);
            img3_to_gui(editor, lim, dimensions);

            SDL_RenderPresent(editor->renderer);
            lim->img_switch = 3;
            printf("Operations done. img_switch: %d\n", lim->img_switch);
        }
   }
}
