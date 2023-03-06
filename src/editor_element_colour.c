#include "drowning.h"

static uint32_t    img3_colouring(t_map *map, int row_now, int col_now)
{
    uint32_t    colour;

    colour = 0x000000FF;
    return (colour);
}

static uint32_t    img2_colouring(t_map *map, int row_now, int col_now)
{
    uint32_t    colour;

    colour = 0x0000FF00;
    return (colour);
}

static uint32_t    colour_entity(t_map *map, int row_now, int col_now)
{
    uint32_t    colour;

    if (map->map[row_now][col_now][3] == 'X')           //player start
        colour = 0x00000000;
    else if (map->map[row_now][col_now][3] == 'Z')      //goal
        colour = 0x00FFFFFF;
    else if (map->map[row_now][col_now][3] == '$')      //monster 1
        colour = 0x00000011;
    else if (map->map[row_now][col_now][3] == '%')
        colour = 0x00000044;
    else if (map->map[row_now][col_now][3] == '&')      //collectible 1
        colour = 0x00001100;
    else if (map->map[row_now][col_now][3] == '@')
        colour = 0x00003300;
    else if (map->map[row_now][col_now][3] == '~')
        colour = 0x00005500;
    return (colour);
}

static uint32_t    colour_wall(t_map *map, int row_now, int col_now)
{
    uint32_t    colour;

    if (map->map[row_now][col_now][0] == '#')
        colour = 0x00CCCC00;
    else if (map->map[row_now][col_now][0] == '1')
        colour = 0x00BBBB00;
    else if (map->map[row_now][col_now][0] == '2')
        colour = 0x00AAAA00;
    else if (map->map[row_now][col_now][0] == '3')
        colour = 0x00999900;
    else if (map->map[row_now][col_now][0] == '4')
        colour = 0x00888800;
    else if (map->map[row_now][col_now][0] == '5')
        colour = 0x00777700;
    else if (map->map[row_now][col_now][0] == '6')
        colour = 0x00666600;
    else if (map->map[row_now][col_now][0] == '7')
        colour = 0x00555500;
    else if (map->map[row_now][col_now][0] == '8')
        colour = 0x00444400;
    return (colour);
}

static uint32_t    img1_colouring(t_map *map, int row_now, int col_now)
{
    uint32_t    colour;

    if (map->map[row_now][col_now][0] != '.')           //walls = yes
        colour = colour_wall(map, row_now, col_now);
    else
    {
        if (map->map[row_now][col_now][3] != '.')       //walls = no, entity = no
            colour = colour_entity(map, row_now, col_now);
        else                                            //walls = no, entity = no, secret = yes
        {
            if (map->map[row_now][col_now][4] == 'R')
                colour = 0x00111111;
            else if (map->map[row_now][col_now][4] == '*')
                colour = 0x00333333;
            else if (map->map[row_now][col_now][4] == '.')
                colour = 0x00666666;
        }
    }
    return (colour);
}

// does not contain a condition for textures (param_index 1)
// does not contain a condition for 45 degree (param_index 2)
uint32_t    element_colour(t_map *map, int row_now, int col_now, int image_switch)
{
    uint32_t    colour;

    if (image_switch == 1)
        colour = img1_colouring(map, row_now, col_now);
    else if (image_switch == 2)
        colour = img2_colouring(map, row_now, col_now);
    else if (image_switch == 3)
        colour = img3_colouring(map, row_now, col_now);
    return (colour);
}
