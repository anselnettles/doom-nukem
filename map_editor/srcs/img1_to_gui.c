#include "../includes/map_editor.h"

static void draw_grid(t_editor *editor, t_editor_images *lim)
{
    t_map_grid  grid;
    int         column_temp;
    int         row_temp;

    grid = (t_map_grid){.x1 = lim->img1_x_min + (IMG1_CATHETUS + 1), .x2 = lim->img1_x_min + (IMG1_CATHETUS + 1),
        .y1 = lim->img_y_min, .y2 = lim->img_y_min + ((IMG1_CATHETUS + 1) * lim->row1 - 1)};
    column_temp = lim->column1;
    SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x11, 0xFF, 0x00);
    //draw vertical gridline
    while (column_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid.x1, grid.y1, grid.x2, grid.y2);
        grid.x1 = grid.x1 + (IMG1_CATHETUS + 1);
        grid.x2 = grid.x1;
        column_temp--;
    }
    row_temp = lim->row1;
    grid = (t_map_grid){.x1 = lim->img1_x_min, .x2 = lim->img1_x_min + ((IMG1_CATHETUS + 1) * lim->column1 - 1),
        .y1 = lim->img_y_min + (IMG1_CATHETUS + 1), .y2 = lim->img_y_min + (IMG1_CATHETUS + 1)};
    //draw horizontal gridline
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid.x1, grid.y1, grid.x2, grid.y2);
        grid.y1 = grid.y1 + (IMG1_CATHETUS + 1);
        grid.y2 = grid.y1;
        row_temp--;
    }
}

static void draw_rect(t_editor *editor, t_editor_images *lim)
{
    SDL_Rect    element_fill;

    element_fill = (SDL_Rect){.x = lim->img1_x_min, .y = lim->img_y_min,
        .w = lim->column1 * (IMG1_CATHETUS + 1), .h = (lim->row1 * (IMG1_CATHETUS + 1))};
    SDL_SetRenderDrawColor(editor->renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(editor->renderer, &element_fill);
}

int img1_to_gui(t_editor *editor, t_mouse *mouse, t_editor_images *lim)
{
/*  load a very transparent story-related background image */
    SDL_RenderClear(editor->renderer);
    draw_rect(editor, lim);
    draw_grid(editor, lim);
    return (0);    
}
