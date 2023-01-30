#include "../includes/map_editor.h"

int main(int argc, char **argv)
{
    t_map   dimensions;

    dimensions = (t_map){.x_to_modify = 0, .y_to_modify = 0, .param_x_to_modify = 0,
        .param_y_to_modify = 0, .param_to_modify = 0};
/*  Activate later
    if (argc != 2)
    {
        tt_errors("Mapfile required as an argument.\nNon-argumented execution may be a feature later.");
        close_program(&editor);
    }
*/
    map_editor(argv[1], &dimensions);
    return (0);
}
