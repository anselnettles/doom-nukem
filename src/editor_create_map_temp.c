#include "drowning.h"

//this can possibly be a single function for ***map and ***map_temp. ***map (read_map()), ***map_temp (here)
void    create_map_temp(t_drown *data)
{
    int     row;
    int     column;
    int     row_temp;
    int     column_temp;

    row_temp = data->editor.images.row1;
    row = 0;
    data->map.map_temp = (char ***)malloc(sizeof(char **) * data->editor.images.row1);
    if (!data->map.map_temp)
    {
        tt_errors("create_map_temp: malloc() fail.\nmap_temp[X][][]");
        exit (-1);
    }
    while (row_temp > 0)
    {
        data->map.map_temp[row] = (char **)malloc(sizeof(char *) * data->editor.images.column1);
        if (!data->map.map_temp[row])
        {
            tt_errors("create_map_temp: malloc() fail.\nmap_temp[][X][]");
            exit (-1);
         }
        column_temp = data->editor.images.column1;
        column = 0;
        while (column_temp > 0)
        {
            data->map.map_temp[row][column] = (char *)malloc(sizeof(char) * (PARAM_COUNT + 1));
            if (!data->map.map_temp[row][column])
            {
                tt_errors("create_map_temp: malloc() fail.\nmap_temp[][][X]");
                exit (-1);
            }
            data->map.map_temp[row][column][PARAM_COUNT] = '\0';
            column++;
            column_temp--;
        }
        row++;
        row_temp--;
    } 
}
