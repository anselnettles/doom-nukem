#include "drowning.h"

void    close_program(t_gfx *gfx)
{
    //free map or map_temp
    SDL_DestroyRenderer(gfx->renderer);
    gfx->renderer = NULL;
    SDL_DestroyWindow(gfx->window);
    gfx->window = NULL;
    (void)gfx;
    SDL_Quit();
    exit(-1);
}
