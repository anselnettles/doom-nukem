#include "../includes/map_editor.h"

static void draw_grid(t_editor *editor, t_editor_images *lim)
{
    t_map_grid  grid_img2;
    int         column_temp;
    int         row_temp;

    //draw vertical grid_img2line
    grid_img2 = (t_map_grid){.x1 = lim->img2_x_min + (IMG2_CATHETUS + 1), .x2 = lim->img2_x_min + (IMG2_CATHETUS + 1),
        .y1 = lim->img_y_min, .y2 = lim->img_y_min + ((IMG2_CATHETUS + 1) * IMG2_PARAM_ROW- 1)};
    column_temp = IMG2_PARAM_COL;
    SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x11, 0xFF, 0x00);
    while (column_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid_img2.x1, grid_img2.y1, grid_img2.x2, grid_img2.y2);
        grid_img2.x1 = grid_img2.x1 + (IMG2_CATHETUS + 1);
        grid_img2.x2 = grid_img2.x1;
        column_temp--;
    }
    //draw horizontal grid_img2line
    row_temp = IMG2_PARAM_ROW;
    grid_img2 = (t_map_grid){.x1 = lim->img2_x_min, .x2 = lim->img2_x_min + ((IMG2_CATHETUS + 1) * IMG2_PARAM_COL - 1),
        .y1 = lim->img_y_min + (IMG2_CATHETUS + 1), .y2 = lim->img_y_min + (IMG2_CATHETUS + 1)};
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid_img2.x1, grid_img2.y1, grid_img2.x2, grid_img2.y2);
        grid_img2.y1 = grid_img2.y1 + (IMG2_CATHETUS + 1);
        grid_img2.y2 = grid_img2.y1;
        row_temp--;
    }
}

static void draw_rect(t_editor *editor, t_editor_images *lim)
{
    SDL_Rect    element_fill;

    element_fill = (SDL_Rect){.x = lim->img2_x_min, .y = lim->img_y_min,
        .w = IMG2_PARAM_COL * (IMG2_CATHETUS + 1), .h = (IMG2_PARAM_ROW * (IMG2_CATHETUS + 1))};
    SDL_SetRenderDrawColor(editor->renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(editor->renderer, &element_fill);
}

int img2_to_gui(t_editor *editor, t_editor_images *lim)
{
    // SDL_RenderClear(editor->renderer);
    draw_rect(editor, lim);
    draw_grid(editor, lim);

    return (0);
}
