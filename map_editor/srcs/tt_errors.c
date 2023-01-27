#include "../includes/map_editor.h"

void    tt_errors(char *error_msg)
{
    while (*error_msg != '\0')
    {
        write(1, error_msg, 1);
        error_msg++;
    }
    write(1, "\n", 1);
}
