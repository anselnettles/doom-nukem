#include "../../src/drowning.h"

int  init(t_gfx *gfx)
{
    int success = 1;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        tt_errors("init: SDL_Init() fail");
        success = 0;
    }
    gfx->window = SDL_CreateWindow("Map Editor", 0, 0,
        WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!gfx->window)
    {
        tt_errors("init: SDL_CreateWindow() fail");
        success = 0;
    }
    gfx->renderer = SDL_CreateRenderer(gfx->window, -1, SDL_RENDERER_ACCELERATED);
    if (!gfx->renderer)
    {
        tt_errors("init: SDL_CreateRenderer() fail");
        success = 0;
    }
    return (success);
}
