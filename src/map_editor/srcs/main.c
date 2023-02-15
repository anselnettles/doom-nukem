#include "../includes/map_editor.h"

int main(int argc, char **argv)
{
    t_map   data;

    data = (t_map){/*.x_to_modify = 0, .y_to_modify = 0, */.param_x_to_modify = 0,
        .param_y_to_modify = 0, .param_to_modify = 0, .selection_index = 0, .map = NULL, .map_temp = NULL,
        .map_x = 0, .map_y = 0, .selection_x = 0, .selection_y = 0};
/*  Activate later
    if (argc != 2)
    {
        tt_errors("Mapfile required as an argument.\nNon-argumented execution may be a feature later.");
        close_program(&editor);
    }
*/
    map_editor(argv[1], &data);
    return (0);
}
