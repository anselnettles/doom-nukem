#include "../includes/map_editor.h"

void    testing_print_map(t_map *data, t_editor_images *images)
{
    int i2;
    int i1;
    int temp_column;
    int temp_row;

    printf("-- map: --\n");
    temp_row = images->row1;
    temp_column = images->column1;
    i2 = 0;
    while (temp_row > 0)
    {
        i1 = 0;
        temp_column = images->column1;
        while (temp_column > 0)
        {
            printf("%s", data->map[i2][i1]);
            printf(" ");
            i1++;
            temp_column--;
        }
        i2++;
        printf("\n");
        temp_row--;
    }

    printf("-- map_temp: --\n");
    temp_row = images->row1;
    temp_column = images->column1;
    i2 = 0;
    while (temp_row > 0)
    {
        i1 = 0;
        temp_column = images->column1;
        while (temp_column > 0)
        {
            printf("%s", data->map_temp[i2][i1]);
            printf(" ");
            i1++;
            temp_column--;
        }
        i2++;
        printf("\n");
        temp_row--;
    }

}
