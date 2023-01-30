#include "../includes/map_editor.h"

//Column/row count of a grid
static void    get_row_and_column_count(int cathetus, t_editor_images *images, int *col_count, int *row_count)
{
    if (cathetus == IMG3_CATHETUS)
    {
        *col_count = images->column3;
        *row_count = images->row3;     //this is get from img1_and_img2/img3_to_gui
    }
}

//Check if mouse coordinates are inside the grid of an image
static int is_mouse_in_grid(t_editor_images *images, t_mouse *mouse, unsigned short int img_switch, int cathetus, t_map *data)
{
    int x;
    int y;
    int col_count;
    int row_count;

    if (img_switch == 3)
    {
        x = mouse->x - images->img3_x_min;
        y = mouse->y - images->img_y_min;
    }
    data->selection_x = (x - (x % (cathetus + 1))) / (cathetus + 1);
    data->selection_y = (y - (y % (cathetus + 1))) / (cathetus + 1);
    get_row_and_column_count(cathetus, images, &col_count, &row_count);
    if (data->selection_x < col_count && data->selection_y < row_count)
        return (1);
    return (0);
}

//Check in which image mouse coordinates are
static int    is_mouse_in_image(t_mouse *mouse, t_editor_images *images, unsigned short int img_switch)
{
    if (img_switch == 3 && (mouse->x >= images->img3_x_min && mouse->x < images->img3_x_max) && (mouse->y > images->img_y_min))
        return (1);
    return (0);
}

int get_m1_pressed_img3_grid_element(t_mouse *mouse, t_map *data, t_editor_images *images)
{
    if ((is_mouse_in_image(mouse, images, images->img_switch) == 1) && images->img_switch == 3)
    {
        if (is_mouse_in_grid(images, mouse, images->img_switch, IMG3_CATHETUS, data) == 1)
            return (1);
    }
    return (0);
}
