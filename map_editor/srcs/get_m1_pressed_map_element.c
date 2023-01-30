#include "../includes/map_editor.h"

//Column/row count of a grid
static void    get_row_and_column_count(int cathetus, t_editor_images *images, int *col_count, int *row_count)
{
    if (cathetus == IMG1_CATHETUS)
    {
        *col_count = images->column1;
        *row_count = images->row1;
    }
    else if (cathetus == IMG2_CATHETUS)
    {
        *col_count = images->column2;
        *row_count = images->row2;
    }
}

//Checks if mouse coordinates are inside the grid of an image
static int is_mouse_in_grid(t_editor_images *images, t_mouse *mouse, unsigned short int img_switch, int cathetus, t_map *data)
{
    int x;
    int y;
    int col_count;
    int row_count;

    if (img_switch == 1)
    {
        x = mouse->x - images->img1_x_min;
        y = mouse->y - images->img_y_min;
        data->map_x = (x - (x % (cathetus + 1))) / (cathetus + 1);
        data->map_y = (y - (y % (cathetus + 1))) / (cathetus + 1);
    }
    else if (img_switch == 2)
    {
        x = mouse->x - images->img2_x_min;
        y = mouse->y - images->img_y_min;
        data->param_x_to_modify = (x - (x % (cathetus + 1))) / (cathetus + 1);
        data->param_y_to_modify = (y - (y % (cathetus + 1))) / (cathetus + 1);
    }
    get_row_and_column_count(cathetus, images, &col_count, &row_count);
    if (img_switch == 1 && (data->map_x < col_count && data->map_y < row_count))
        return (1);
    else if (img_switch == 2 && (data->param_x_to_modify < col_count && data->param_y_to_modify < row_count))
        return (1);
    return (0);
}

//Check in which image mouse coordinates are
static int    is_mouse_in_image(t_mouse *mouse, t_editor_images *images, unsigned short int img_switch)
{
    if (img_switch == 1 && (mouse->x >= images->img1_x_min && mouse->x < images->img1_x_max) && (mouse->y > images->img_y_min))
        return (1);
    if (img_switch == 2 && (mouse->x >= images->img2_x_min && mouse->x < images->img2_x_max) && (mouse->y > images->img_y_min))
        return (1);
    return (0);
}

int get_m1_pressed_map_element(t_mouse *mouse, t_map *data, t_editor_images *images)
{
    if ((is_mouse_in_image(mouse, images, images->img_switch) == 1) && images->img_switch == 1)
    {
        if (is_mouse_in_grid(images, mouse, images->img_switch, IMG1_CATHETUS, data) == 1)
            return (1);
    }
    else if ((is_mouse_in_image(mouse, images, images->img_switch) == 1) && images->img_switch == 2)
    {
        if (is_mouse_in_grid(images, mouse, images->img_switch, IMG2_CATHETUS, data) == 1)
            return (1);
    }
    return (0);
}
