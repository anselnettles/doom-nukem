#include "../includes/map_editor.h"

//Column/row count of a grid
static void    get_row_and_column_count(int cathetus, t_editor_images *lim, int *col_count, int *row_count)
{
    if (cathetus == IMG1_CATHETUS)
    {
        *col_count = lim->column1;
        *row_count = lim->row1;
    }
    else if (cathetus == IMG2_CATHETUS)
    {
        *col_count = lim->column2;
        *row_count = lim->row2;
    }
    /*else if (cathetus == IMG3_CATHETUS)
    {
        *col_count = lim->column3;
        *row_count = lim->row3;          //img3 logic error. This is calculated the first time in param_to_modify()
    }*/
}

//Check if mouse coordinates are inside the grid of an image
static int is_mouse_in_grid(t_editor_images *lim, t_mouse *mouse, unsigned short int img_switch, int cathetus)
{
    int x;
    int y;
    int col_count;
    int row_count;

    if (img_switch == 1)
    {
        x = mouse->x - lim->img1_x_min;
        y = mouse->y - lim->img_y_min;
    }
    if (img_switch == 2)
    {
        x = mouse->x - lim->img2_x_min;
        y = mouse->y - lim->img_y_min;
    }
    /*if (img_switch == 3)                //img3 logic error. This vanishes
    {
        x = mouse->x - lim->img3_x_min;
        y = mouse->y - lim->img_y_min;
    }*/
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
    if (img_switch == 1 && (mouse->x >= lim->img1_x_min && mouse->x < lim->img1_x_max) && (mouse->y > lim->img_y_min))
        return (1);
    if (img_switch == 2 && (mouse->x >= lim->img2_x_min && mouse->x < lim->img2_x_max) && (mouse->y > lim->img_y_min))
        return (1);
    /*if (img_switch == 3 && (mouse->x >= lim->img3_x_min && mouse->x < lim->img3_x_max) && (mouse->y > lim->img_y_min))
        return (1);     //img3 logic error.*/
    return (0);
}

int get_m1_pressed_map_element(t_mouse *mouse, t_map *dimensions, t_editor_images *lim)
{
    if ((is_mouse_in_image(mouse, lim, lim->img_switch) == 1) && lim->img_switch == 1)
    {
        if (is_mouse_in_grid(lim, mouse, lim->img_switch, IMG1_CATHETUS) == 1)
            return (1);
    }
    else if ((is_mouse_in_image(mouse, lim, lim->img_switch) == 1) && lim->img_switch == 2)
    {
        if (is_mouse_in_grid(lim, mouse, lim->img_switch, IMG2_CATHETUS) == 1)
            return (1);
    }
    /*else if ((is_mouse_in_image(mouse, lim, lim->img_switch) == 1) && lim->img_switch == 3) //img3 logic error.
    {
        if (is_mouse_in_grid(lim, mouse, lim->img_switch, IMG3_CATHETUS) == 1)
            return (1);
    }*/
    return (0);
}
