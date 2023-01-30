#include "../includes/map_editor.h"

void    param_to_modify(t_map *dimensions)
{
    if (dimensions->param_x_to_modify == 0 && dimensions->param_y_to_modify == 0)
        dimensions->param_to_modify = 0;
    else if (dimensions->param_x_to_modify == 1 && dimensions->param_y_to_modify == 0)
        dimensions->param_to_modify = 1;
    else if (dimensions->param_x_to_modify == 0 && dimensions->param_y_to_modify == 1)
        dimensions->param_to_modify = 2;
    else if (dimensions->param_x_to_modify == 1 && dimensions->param_y_to_modify == 1)
        dimensions->param_to_modify = 3;
    else
    {
        tt_errors("param_to_modify() fail. Undefined error.");
        exit(-1);
    }
}
