#include "../includes/map_editor.h"

/*
    Checks if 'S' was pressed.
    Return 1 on success, 0 on fail
*/
int save_changes(t_editor *editor)
{
    if (editor->event.type == SDL_KEYDOWN)   
    {
        if (editor->event.key.keysym.sym == SDLK_s)
            return (1);    
    }
    return (0);
}
