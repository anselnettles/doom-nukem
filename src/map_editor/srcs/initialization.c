#include "../includes/map_editor.h"

/*
    insert comments
*/
// 5 variables. Consider inserting char *map_file to one of the structs (however this is useless weight along the program)
void    initialization(t_editor_images *images, t_map *data, t_character *chars, char *map_file, t_editor *editor)
{
    set_image_limits(images);
    set_values_for_parameters(chars);
    read_map(map_file, data, images, editor);
    create_map_temp(data, images);
    copy_map_to_map_temp(data, images);
    if (validate_map_temp(data, images, chars) != 1)
        tt_errors("main: validate_map_temp() fail.");
}
