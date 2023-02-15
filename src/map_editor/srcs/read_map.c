#include "../../src/drowning.h"

/*
	Modify read_map.c
	Should allow non-NL map files to be read.

	...
    while (*buf != '\0')
    {
        while (*buf != ' ' && *buf != '\n' && *buf != '\0')
		{
			...
		}
		...
	}
*/


/*
    Inserts the values char *buf into char ***map.
*/
static void buffer_to_3D_map_array(char *buf, t_map *map)
{
    int i2;
    int i1;
    int i0;

    i2 = 0;
    i1 = 0;
    i0 = 0;
    while (*buf != '!')
    {
        while (*buf != ' ' && *buf != '\n' && *buf != '!')
        {
            map->map[i2][i1][i0] = *buf;
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

//this can possibly be a single function for ***map and ***map_temp. ***map (read_map()), ***map_temp (here)
static void malloc_3D_map_array(t_map *map, t_editor_images *images)
{
    int     row;
    int     column;
    int     row_temp;
    int     column_temp;

    row_temp = images->row1;
    row = 0;
    map->map = (char ***)malloc(sizeof(char **) * images->row1);
    if (!map->map)
    {
        tt_errors("malloc_3d_map_array: malloc() fail.\nmap[X][][]");
        exit (-1);
    }
    while (row_temp > 0)
    {
        map->map[row] = (char **)malloc(sizeof(char *) * images->column1);
        if (!map->map[row])
        {
            tt_errors("malloc_3d_map_array: malloc() fail.\nmap[][X][]");
            exit (-1);
         }
        column_temp = images->column1;
        column = 0;
        while (column_temp > 0)
        {
            map->map[row][column] = (char *)malloc(sizeof(char) * (PARAM_COUNT + 1));
            if (!map->map[row][column])
            {
                tt_errors("malloc_3d_map_array: malloc() fail.\nmap[][][X]");
                exit (-1);
            }
            map->map[row][column][PARAM_COUNT] = '!';
            column++;
            column_temp--;
        }
        row++;
        row_temp--;
    } 
}

/*
    Counts rows and columns of the map file. Map file is standardized to be square-shaped.
*/
static void count_map_data(char *buf, t_map *map, t_editor_images *images)
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
    images->column1 = (row_bytes + 1) / (PARAM_COUNT + 1);
    while(*buf != '!')
    {
        if (*buf == '\n')
            images->row1++;
        buf++;
    }
}

/*
    Reads a map file into a char *buf and converts the buf to char ***map.
*/
void    read_map(char *map_file, t_map *map, t_editor_images *images, t_gfx *gfx)
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
    if (validate_buffer_format(buf, images) != 1)
    {
        tt_errors("read_map: validate_buffer_format() fail.");
        exit(-1);
    }
        
    parse_map_file_to_arrays(buf, gfx); //maptype: int. insert into if (function() != 1)
    count_map_data(buf, map, images);
    malloc_3D_map_array(map, images);
    buffer_to_3D_map_array(buf, map);
}
