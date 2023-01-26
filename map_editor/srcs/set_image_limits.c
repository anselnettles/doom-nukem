#include "../includes/map_editor.h"

void    set_image_limits(t_editor_images *lim)
{
    lim->img1_x_min = SCREEN_W * 0.05;
    lim->img2_x_min = SCREEN_W * 0.625; // 1280 * 0.625 = 800
    lim->img1_x_max = lim->img2_x_min - 1;
    lim->img3_x_min = SCREEN_W * 0.78125; // 1280 = 0.78125 = 1000
    lim->img2_x_max = lim->img3_x_min - 1;
    lim->img3_x_max = SCREEN_W;
    lim->img_y_min = SCREEN_H * 0.05;
    lim->img_y_max = SCREEN_H;
    //these indicate which map[y][x] is being referred to
    lim->map_x = 0;
    lim->map_y = 0;
    //switch between the three images: 1 - 3, 1 referring the default map grid image 
    lim->img_switch = 1;
    //grid 2 and 3 have fixed column and row count. row1 and column1 will be set in read_map()
    lim->row1 = 0;
    lim->column1 = 0;
    lim->row2 = IMG2_PARAM_ROW;
    lim->column2 = IMG2_PARAM_COL;
    lim->row3 = 0;  //img3 logic error - keep initial at 0. First time calculated in img3_to_gui/get_param_row
    lim->column3 = IMG3_PARAM_COL; /* Check if this used anywhere? same for row2/col2 */
    lim->selection_index = 0;
}
