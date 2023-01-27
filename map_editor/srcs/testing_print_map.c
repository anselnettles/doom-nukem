#include "../includes/map_editor.h"

void    testing_print_map(t_map dimensions, t_editor_images lim)
{
    int i2;
    int i1;
    int temp_column;
    int temp_row;

    i2 = 0;
    while (lim.row1 > 0)
    {
        i1 = 0;
        temp_column = lim.column1;
        while (temp_column > 0)
        {
            printf("%s", dimensions.map[i2][i1]);
            printf(" ");
            i1++;
            temp_column--;
        }
        i2++;
        printf("\n");
        lim.row1--;
    }
}
