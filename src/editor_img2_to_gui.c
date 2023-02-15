#include "drowning.h"

/*
    insert comments
*/
static void draw_grid(t_gfx *gfx, t_editor_images *images)
{
    t_map_grid  grid_img2;
    int         column_temp;
    int         row_temp;

    //draw vertical grid_img2line
    grid_img2 = (t_map_grid){.x1 = images->img2_x_min + (IMG2_CATHETUS + 1), .x2 = images->img2_x_min + (IMG2_CATHETUS + 1),
        .y1 = images->img_y_min, .y2 = images->img_y_min + ((IMG2_CATHETUS + 1) * IMG2_PARAM_ROW- 1)};
    column_temp = IMG2_PARAM_COL;
    SDL_SetRenderDrawColor(gfx->renderer, 0x00, 0x11, 0xFF, 0x00);
    while (column_temp > 1)
    {
        SDL_RenderDrawLine(gfx->renderer, grid_img2.x1, grid_img2.y1, grid_img2.x2, grid_img2.y2);
        grid_img2.x1 = grid_img2.x1 + (IMG2_CATHETUS + 1);
        grid_img2.x2 = grid_img2.x1;
        column_temp--;
    }
    //draw horizontal grid_img2line
    row_temp = IMG2_PARAM_ROW;
    grid_img2 = (t_map_grid){.x1 = images->img2_x_min, .x2 = images->img2_x_min + ((IMG2_CATHETUS + 1) * IMG2_PARAM_COL - 1),
        .y1 = images->img_y_min + (IMG2_CATHETUS + 1), .y2 = images->img_y_min + (IMG2_CATHETUS + 1)};
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(gfx->renderer, grid_img2.x1, grid_img2.y1, grid_img2.x2, grid_img2.y2);
        grid_img2.y1 = grid_img2.y1 + (IMG2_CATHETUS + 1);
        grid_img2.y2 = grid_img2.y1;
        row_temp--;
    }
}

static void draw_rect(t_gfx *gfx, t_editor_images *images)
{
    SDL_Rect    element_fill;

    element_fill = (SDL_Rect){.x = images->img2_x_min, .y = images->img_y_min,
        .w = IMG2_PARAM_COL * (IMG2_CATHETUS + 1), .h = (IMG2_PARAM_ROW * (IMG2_CATHETUS + 1))};
    SDL_SetRenderDrawColor(gfx->renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(gfx->renderer, &element_fill);
}

int img2_to_gui(t_gfx *gfx, t_editor_images *images)
{
    // SDL_RenderClear(editor->renderer);
    draw_rect(gfx, images);
    draw_grid(gfx, images);

    return (0);
}
