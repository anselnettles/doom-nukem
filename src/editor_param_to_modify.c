#include "drowning.h"

/*
    Selects the parameter to be modified in img2 grid.
*/
void    param_to_modify(t_map *map)
{
    if (map->param_x_to_modify == 0 && map->param_y_to_modify == 0)
        map->param_to_modify = 0;
    else if (map->param_x_to_modify == 1 && map->param_y_to_modify == 0)
        map->param_to_modify = 1;
    else if (map->param_x_to_modify == 0 && map->param_y_to_modify == 1)
        map->param_to_modify = 2;
    else if (map->param_x_to_modify == 1 && map->param_y_to_modify == 1)
        map->param_to_modify = 3;
    else if (map->param_x_to_modify == 0 && map->param_y_to_modify == 2)
        map->param_to_modify = 4;
    else if (map->param_x_to_modify == 1 && map->param_y_to_modify == 2)
    {
        printf("sixth param does not exist. This param_element will not be drawn in the final program\n");
        exit(-1);
    }
    else
    {
        tt_errors("param_to_modify() fail. Undefined error.");
        exit(-1);
    }
}
