#include "../includes/map_editor.h"

static void draw_grid(t_editor *editor, t_editor_images *lim)
{
    t_map_grid  grid_img3;
    int         column_temp;
    int         row_temp;

    //draw horizontal gridline
    SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x11, 0xFF, 0x00);
    row_temp = lim->row3;   //might need to be reset to 0 after img3 open/save
    grid_img3 = (t_map_grid){.x1 = lim->img3_x_min, .x2 = lim->img3_x_min + ((IMG3_CATHETUS + 1) * IMG3_PARAM_COL - 1),
        .y1 = lim->img_y_min + (IMG3_CATHETUS + 1), .y2 = lim->img_y_min + (IMG3_CATHETUS + 1)};
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid_img3.x1, grid_img3.y1, grid_img3.x2, grid_img3.y2);
        grid_img3.y1 = grid_img3.y1 + (IMG3_CATHETUS + 1);
        grid_img3.y2 = grid_img3.y1;
        row_temp--;
    }
}

// This function will define the rows in img3, i.e. the selection count for each parameter.
static void    get_param_row(t_editor_images *lim, t_map *dimensions)
{
    if (dimensions->param_to_modify == 0)
        lim->row3 = 6;
    else if (dimensions->param_to_modify == 1)
        lim->row3 = 4;
    else if (dimensions->param_to_modify == 2)
        lim->row3 = 3;
    else if (dimensions->param_to_modify == 3)
        lim->row3 = 2;
}

static void draw_rect(t_editor *editor, t_editor_images *lim, t_map *dimensions)
{
    SDL_Rect    element_fill;

    get_param_row(lim, dimensions);
    element_fill = (SDL_Rect){.x = lim->img3_x_min, .y = lim->img_y_min,
        .w = IMG3_PARAM_COL * (IMG3_CATHETUS + 1), .h = (lim->row3 * (IMG3_CATHETUS + 1))};
    SDL_SetRenderDrawColor(editor->renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(editor->renderer, &element_fill);
}

int img3_to_gui(t_editor *editor, t_editor_images *lim, t_map *dimensions)
{
    draw_rect(editor, lim, dimensions);
    draw_grid(editor, lim);
    return (0);
}

/* BU original img3_to_gui without dynamic row count
#include "../includes/map_editor.h"

static void draw_grid(t_editor *editor, t_editor_images *lim)
{
    t_map_grid  grid_img3;
    int         column_temp;
    int         row_temp;

    //draw horizontal grid_img2line
    SDL_SetRenderDrawColor(editor->renderer, 0x00, 0x11, 0xFF, 0x00);
    row_temp = IMG3_PARAM_ROW;
    grid_img3 = (t_map_grid){.x1 = lim->img3_x_min, .x2 = lim->img3_x_min + ((IMG3_CATHETUS + 1) * IMG3_PARAM_COL - 1),
        .y1 = lim->img_y_min + (IMG3_CATHETUS + 1), .y2 = lim->img_y_min + (IMG3_CATHETUS + 1)};
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(editor->renderer, grid_img3.x1, grid_img3.y1, grid_img3.x2, grid_img3.y2);
        grid_img3.y1 = grid_img3.y1 + (IMG3_CATHETUS + 1);
        grid_img3.y2 = grid_img3.y1;
        row_temp--;
    }
}

static void draw_rect(t_editor *editor, t_editor_images *lim)
{
    SDL_Rect    element_fill;

    element_fill = (SDL_Rect){.x = lim->img3_x_min, .y = lim->img_y_min,
        .w = IMG3_PARAM_COL * (IMG3_CATHETUS + 1), .h = (IMG3_PARAM_ROW * (IMG3_CATHETUS + 1))};
    SDL_SetRenderDrawColor(editor->renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(editor->renderer, &element_fill);
}

int img3_to_gui(t_editor *editor, t_editor_images *lim)
{
    // SDL_RenderClear(editor->renderer);
    draw_rect(editor, lim);
    draw_grid(editor, lim);

    return (0);
}
*/