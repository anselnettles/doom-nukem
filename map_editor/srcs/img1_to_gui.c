#include "../includes/map_editor.h"

static void draw_grid(t_editor *editor, t_editor_images *images)
{
    t_map_grid  grid;
    int         column_temp;
    int         row_temp;

    grid = (t_map_grid){.x1 = images->img1_x_min + (IMG1_CATHETUS + 1), .x2 = images->img1_x_min + (IMG1_CATHETUS + 1),
        .y1 = images->img_y_min, .y2 = images->img_y_min + ((IMG1_CATHETUS + 1) * images->row1 - 1)};
    column_temp = images->column1;
    SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x11, 0xFF, 0x00);
    //draw vertical gridline
    while (column_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid.x1, grid.y1, grid.x2, grid.y2);
        grid.x1 = grid.x1 + (IMG1_CATHETUS + 1);
        grid.x2 = grid.x1;
        column_temp--;
    }
    row_temp = images->row1;
    grid = (t_map_grid){.x1 = images->img1_x_min, .x2 = images->img1_x_min + ((IMG1_CATHETUS + 1) * images->column1 - 1),
        .y1 = images->img_y_min + (IMG1_CATHETUS + 1), .y2 = images->img_y_min + (IMG1_CATHETUS + 1)};
    //draw horizontal gridline
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid.x1, grid.y1, grid.x2, grid.y2);
        grid.y1 = grid.y1 + (IMG1_CATHETUS + 1);
        grid.y2 = grid.y1;
        row_temp--;
    }
}

static void draw_rect(t_editor *editor, t_editor_images *images)
{
    SDL_Rect    element_fill;

    element_fill = (SDL_Rect){.x = images->img1_x_min, .y = images->img_y_min,
        .w = images->column1 * (IMG1_CATHETUS + 1), .h = (images->row1 * (IMG1_CATHETUS + 1))};
    SDL_SetRenderDrawColor(editor->renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(editor->renderer, &element_fill);
}

int img1_to_gui(t_editor *editor, t_mouse *mouse, t_editor_images *images)
{
/*  load a very transparent story-related background image */
    SDL_RenderClear(editor->renderer);
    draw_rect(editor, images);
    draw_grid(editor, images);
    return (0);    
}
