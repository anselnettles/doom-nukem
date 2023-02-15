#include "drowning.h"

/*
    insert comments

    renaming
*/
void    img1_and_img2(t_gfx *gfx, t_map *map, t_mouse *mouse, t_editor_images *images)
{
    if (gfx->event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (gfx->event.button.button == SDL_BUTTON_LEFT && images->img_switch == 1)
        {
            printf("img1: map_x %d, map_y %d | switch to img2\n", map->map_x, map->map_y);
            SDL_RenderClear(gfx->renderer);
            SDL_SetRenderDrawColor(gfx->renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(gfx, mouse, images); 
            img2_to_gui(gfx, images);
            SDL_RenderPresent(gfx->renderer);
            images->img_switch = 2;
        }
        else if (gfx->event.button.button == SDL_BUTTON_LEFT && images->img_switch == 2)
        {
            SDL_RenderClear(gfx->renderer);
            SDL_SetRenderDrawColor(gfx->renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(gfx, mouse, images); 
            img2_to_gui(gfx, images);
            param_to_modify(map);
            img3_to_gui(gfx, images, map);
            SDL_RenderPresent(gfx->renderer);
            images->img_switch = 3;
            printf("img2: param_to_modify: %d | switch to img3\n", map->param_to_modify);
        }
   }
}
