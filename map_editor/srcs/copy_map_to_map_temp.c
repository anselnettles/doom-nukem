#include "../includes/map_editor.h"

void    copy_map_to_map_temp(t_map *data, t_editor_images *images)
{
    int i0;
    int i1;
    int i2;

    i0 = 0;
    i1 = 0;
    i2 = 0;
    while (i2 < images->row1)
    {
        i1 = 0;
        while (i1 < images->column1)
        {
            i0 = 0;
            while (i0 < PARAM_COUNT)
            {
                data->map_temp[i2][i1][i0] = data->map[i2][i1][i0];
                i0++;
            }
            i1++;
        }
        i2++;
    }
}
