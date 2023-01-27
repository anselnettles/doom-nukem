#include "../includes/map_editor.h"

//Column/row count of a grid
static void    get_row_and_column_count(int cathetus, t_editor_images *lim, int *col_count, int *row_count)
{
    if (cathetus == IMG3_CATHETUS)
    {
        *col_count = lim->column3;
        *row_count = lim->row3;     //this is get from img1_and_img2/img3_to_gui
    }
}

//Check if mouse coordinates are inside the grid of an image
static int is_mouse_in_grid(t_editor_images *lim, t_mouse *mouse, unsigned short int img_switch, int cathetus)
{
    int x;
    int y;
    int col_count;
    int row_count;

    if (img_switch == 3)
    {
        x = mouse->x - lim->img3_x_min;
        y = mouse->y - lim->img_y_min;
    }
    lim->map_x = (x - (x % (cathetus + 1))) / (cathetus + 1);
    lim->map_y = (y - (y % (cathetus + 1))) / (cathetus + 1);
    get_row_and_column_count(cathetus, lim, &col_count, &row_count);
    if (lim->map_x < col_count && lim->map_y < row_count)
        return (1);
    return (0);
}

//Check in which image mouse coordinates are
static int    is_mouse_in_image(t_mouse *mouse, t_editor_images *lim, unsigned short int img_switch)
{
    if (img_switch == 3 && (mouse->x >= lim->img3_x_min && mouse->x < lim->img3_x_max) && (mouse->y > lim->img_y_min))
        return (1);
    return (0);
}

int get_m1_pressed_img3_grid_element(t_mouse *mouse, t_map *dimensions, t_editor_images *lim)
{
    if ((is_mouse_in_image(mouse, lim, lim->img_switch) == 1) && lim->img_switch == 3)
    {
        if (is_mouse_in_grid(lim, mouse, lim->img_switch, IMG3_CATHETUS) == 1)
            return (1);
    }
    return (0);
}
