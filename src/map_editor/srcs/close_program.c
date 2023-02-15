#include "../includes/map_editor.h"

void    close_program(t_editor *editor)
{
    //free map or map_temp
    SDL_DestroyRenderer(editor->renderer);
    editor->renderer = NULL;
    SDL_DestroyWindow(editor->window);
    editor->window = NULL;
    (void)editor;
    SDL_Quit();
    exit(-1);
}
