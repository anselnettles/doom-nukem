#include "drowning.h"

/*
    insert comments
*/
static void draw_grid(t_gfx *gfx, t_editor_images *images)
{
    t_map_grid  grid_img3;
    int         column_temp;
    int         row_temp;

    //draw horizontal gridline
    SDL_SetRenderDrawColor(gfx->renderer, 0x00, 0x11, 0xFF, 0x00);
    row_temp = images->row3;   //might need to be reset to 0 after img3 open/save
    grid_img3 = (t_map_grid){.x1 = images->img3_x_min, .x2 = images->img3_x_min + ((IMG3_CATHETUS + 1) * IMG3_PARAM_COL - 1),
        .y1 = images->img_y_min + (IMG3_CATHETUS + 1), .y2 = images->img_y_min + (IMG3_CATHETUS + 1)};
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(gfx->renderer, grid_img3.x1, grid_img3.y1, grid_img3.x2, grid_img3.y2);
        grid_img3.y1 = grid_img3.y1 + (IMG3_CATHETUS + 1);
        grid_img3.y2 = grid_img3.y1;
        row_temp--;
    }
}

// This function will define the rows in img3, i.e. the selection count for each parameter.
static void    get_param_row(t_editor_images *images, t_map *map)
{
    if (map->param_to_modify == 0)
        images->row3 = 10;
    else if (map->param_to_modify == 1)
        images->row3 = 4;
    else if (map->param_to_modify == 2)
        images->row3 = 5;
    else if (map->param_to_modify == 3)
        images->row3 = 8;
    else if (map->param_to_modify == 4)
        images->row3 = 3;
}

static void draw_rect(t_gfx *gfx, t_editor_images *images, t_map *map)
{
    SDL_Rect    element_fill;

    get_param_row(images, map);
    element_fill = (SDL_Rect){.x = images->img3_x_min, .y = images->img_y_min,
        .w = IMG3_PARAM_COL * (IMG3_CATHETUS + 1), .h = (images->row3 * (IMG3_CATHETUS + 1))};
    SDL_SetRenderDrawColor(gfx->renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(gfx->renderer, &element_fill);
}

int img3_to_gui(t_drown *data)
{
    draw_rect(&data->gfx, &data->editor.images, &data->map);
    draw_grid(&data->gfx, &data->editor.images);
    return (0);
}
