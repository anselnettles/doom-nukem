#include "drowning.h"

/*
    Insert comments
*/
static void    get_param_row3(t_editor_images *images, t_map *map)
{
    if (map->param_to_modify == 0)
        images->row3 = 12;
    else if (map->param_to_modify == 1)
        images->row3 = 4;
    else if (map->param_to_modify == 2)
        images->row3 = 5;
    else if (map->param_to_modify == 3)
        images->row3 = 8;
    else if (map->param_to_modify == 4)
        images->row3 = 5;
}

static void get_col_row_max(t_drown *data, int *row_max, int *col_max, int image_switch)
{
    if (image_switch == 1)
    {
        *row_max = data->editor.images.row1;
        *col_max = data->editor.images.column1;
    }
    else if (image_switch == 2)
    {
        *row_max = IMG2_PARAM_ROW;
        *col_max = IMG2_PARAM_COL;
    }
    else if (image_switch == 3)
    {
        *row_max = data->editor.images.row3;
        *col_max = IMG3_PARAM_COL;
    }
}

/*
    Insert comments
*/
static void    draw_grid_of_squares_mod(t_drown *data, int cathetus, int img_x_min)
{
    int row_now;
    int col_now;
    int row_max;
    int col_max;

    row_max = 0;
    col_max = 0;
    if (data->editor.images.img_switch == 3)
        get_param_row3(&data->editor.images, &data->map);
    get_col_row_max(data, &row_max, &col_max, data->editor.images.img_switch);
    data->editor.interval.y_start = data->editor.images.img_y_min;
    data->editor.interval.y_end = data->editor.interval.y_start + cathetus;
    row_now = 0;
    while (row_now < row_max)
    {
        col_now = 0;
        data->editor.interval.x_start = img_x_min;
        data->editor.interval.x_end = data->editor.interval.x_start + (cathetus - 1);
        while (col_now < col_max)
        {
            data->editor.interval.colour = element_colour(&data->map, row_now, col_now, data->editor.images.img_switch);
            draw_one_square(&data->gfx, &data->editor.interval);
            col_now++;
            data->editor.interval.x_start = data->editor.interval.x_end + 2;
            data->editor.interval.x_end = data->editor.interval.x_start + (cathetus - 1);
        }
        row_now++;
        data->editor.interval.y_start = data->editor.interval.y_end + 2;
        data->editor.interval.y_end = data->editor.interval.y_start + (cathetus - 1);
    }
}

/*
    Insert comments
*/
void    draw_grid_of_squares(t_drown *data)
{
    if (data->editor.images.img_switch == 1)
        draw_grid_of_squares_mod(data, IMG1_CATHETUS, data->editor.images.img1_x_min);
    else if (data->editor.images.img_switch == 2)
        draw_grid_of_squares_mod(data, IMG2_CATHETUS, data->editor.images.img2_x_min);
    else if (data->editor.images.img_switch == 3)
        draw_grid_of_squares_mod(data, IMG3_CATHETUS, data->editor.images.img3_x_min);
}
