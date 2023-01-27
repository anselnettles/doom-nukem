#include "../includes/map_editor.h"

int  init(t_editor *editor)
{
    int success = 1;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        tt_errors("init: SDL_Init() fail");
        success = 0;
    }
    editor->window = SDL_CreateWindow("Map Editor", 0, 0,
        SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
    if (!editor->window)
    {
        tt_errors("init: SDL_CreateWindow() fail");
        success = 0;
    }
    editor->renderer = SDL_CreateRenderer(editor->window, -1, SDL_RENDERER_ACCELERATED);
    if (!editor->renderer)
    {
        tt_errors("init: SDL_CreateRenderer() fail");
        success = 0;
    }
    return (success);
}
