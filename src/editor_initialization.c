#include "drowning.h"

/*
    insert comments
*/
// 5 variables. Consider inserting char *map_file to one of the structs (however this is useless weight along the program)
void    initialization(t_drown *data, char *map_file)
{
    set_image_limits(&data->editor.images);
    set_values_for_parameters(&data->editor.chars);
    printf("here\n");
    read_map(map_file, data);
    printf("here2\n");
    create_map_temp(data);
    copy_map_to_map_temp(data);
    if (validate_map_temp(data) != 1)
        tt_errors("main: validate_map_temp() fail.");
}
