#include "../includes/map_editor.h"

static void buffer_to_3D_map_array(char *buf, t_map *dimensions)
{
    int i2;
    int i1;
    int i0;

    i2 = 0;
    i1 = 0;
    i0 = 0;
    while (*buf != '\0')
    {
        while (*buf != ' ' && *buf != '\n')
        {
            dimensions->map[i2][i1][i0] = *buf;
            i0++;
            buf++;
        }
        if (*buf == ' ')
        {   
            i0 = 0;
            i1++;
            buf++;
        }
        if (*buf == '\n')
        {
            i0 = 0;
            i1 = 0;
            i2++;
            buf++;
        }
    }
}

static void malloc_3D_map_array(t_map *dimensions, t_editor_images *lim)
{
    //map[row][column][parameter]
    int     row;
    int     column;
    int     row_temp;
    int     column_temp;

    row_temp = lim->row1;
    row = 0;
    dimensions->map = (char ***)malloc(sizeof(char **) * lim->row1);
    if (!dimensions->map)
    {
        tt_errors("malloc_3d_map_array: malloc() fail.\nmap[X][][]");
        exit (-1);
    }
    while (row_temp > 0)
    {
        dimensions->map[row] = (char **)malloc(sizeof(char *) * lim->column1);
        if (!dimensions->map[row])
        {
            tt_errors("malloc_3d_map_array: malloc() fail.\nmap[][X][]");
            exit (-1);
         }
        column_temp = lim->column1;
        column = 0;
        while (column_temp > 0)
        {
            //We have discussed the parameter count per map element is 4. 
            dimensions->map[row][column] = (char *)malloc(sizeof(char) * (PARAM_COUNT + 1));
            if (!dimensions->map[row][column])
            {
                tt_errors("malloc_3d_map_array: malloc() fail.\nmap[][][X]");
                exit (-1);
            }
            dimensions->map[row][column][PARAM_COUNT] = '\0';
            column++;
            column_temp--;
        }
        row++;
        row_temp--;
    } 
}

//Currently the map data file is dictated to be a square, despite the movement area shape
static void count_map_dimensions(char *buf, t_map *dimensions, t_editor_images *lim)
{
    //row_bytes = number of bytes per row
    int row_bytes;

    row_bytes = 0;
    while (*buf != '\n')
    {
        row_bytes++;
        buf++;
    }
    //Each map element has been agreed to contain 4 parameters,
    //  thus number of columns per row is (row_bytes / parameter(=4)).
    //Addition "+ 1" to row_bytes is only a beauty element,
    //  since after the last map element there is '\n' instead of ' '.
    //  Addition "+ 1" to PARAM_COUNT negates ' ' between the elements.
    lim->column1 = (row_bytes + 1) / (PARAM_COUNT + 1);
    while(*buf != '\0')
    {
        if (*buf == '\n')
            lim->row1++;
        buf++;
    }
}

void    read_map(char *map_file, t_map *dimensions, t_editor_images *lim)
{
    int     fd;
    int     ret;
    char    buf[BUF_SIZE + 1];

    fd = open(map_file, O_RDONLY);
    if (fd < 0)
    {
        tt_errors("read_map: open() fail.");
        exit(-1);
    }
    ret = read(fd, buf, BUF_SIZE);
    if (ret <= 0)
    {
        tt_errors("read_map: read() fail.\nEmpty, invalid or inaccessible map file.");
        exit(-1);
    }
    buf[ret] = '\0';
    //validate_map(buf);
    count_map_dimensions(buf, dimensions, lim);
    malloc_3D_map_array(dimensions, lim);
    buffer_to_3D_map_array(buf, dimensions);
}
