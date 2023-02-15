#include "../includes/map_editor.h"

/*
    Sets limits for images. Initializes switch between images, whereas row/col count.
*/
void    set_image_limits(t_editor_images *images)
{
    images->img1_x_min = SCREEN_W * 0.05;
    images->img2_x_min = SCREEN_W * 0.625; // 1280 * 0.625 = 800
    images->img1_x_max = images->img2_x_min - 1;
    images->img3_x_min = SCREEN_W * 0.78125; // 1280 = 0.78125 = 1000
    images->img2_x_max = images->img3_x_min - 1;
    images->img3_x_max = SCREEN_W;
    images->img_y_min = SCREEN_H * 0.05;
    images->img_y_max = SCREEN_H;
    //switch between the three images: 1 - 3, 1 referring to the default map grid
    images->img_switch = 1;
    //grid 2 and 3 have fixed column and row count. row1 and column1 will be calculated in read_map()
    images->row1 = 0;
    images->column1 = 0;
    images->row2 = IMG2_PARAM_ROW;
    images->column2 = IMG2_PARAM_COL;
    //Initial .row3 = 0. First time calculated in img3_to_gui/get_param_row
    images->row3 = 0;
    images->column3 = IMG3_PARAM_COL;
}
