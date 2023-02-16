#include "drowning.h"

/*
    insert comments
*/
static void draw_grid(t_drown *data)
{
    t_map_grid  grid;
    int         column_temp;
    int         row_temp;

    grid = (t_map_grid){.x1 = data->editor.images.img1_x_min + (IMG1_CATHETUS + 1), .x2 = data->editor.images.img1_x_min + (IMG1_CATHETUS + 1),
        .y1 = data->editor.images.img_y_min, .y2 = data->editor.images.img_y_min + ((IMG1_CATHETUS + 1) * data->editor.images.row1 - 1)};
    column_temp = data->editor.images.column1;
    SDL_SetRenderDrawColor(data->gfx.renderer, 0x00, 0x11, 0xFF, 0x00);
    //draw vertical gridline
    while (column_temp > 1)
    {
        SDL_RenderDrawLine(data->gfx.renderer, grid.x1, grid.y1, grid.x2, grid.y2);
        grid.x1 = grid.x1 + (IMG1_CATHETUS + 1);
        grid.x2 = grid.x1;
        column_temp--;
    }
    row_temp = data->editor.images.row1;
    grid = (t_map_grid){.x1 = data->editor.images.img1_x_min, .x2 = data->editor.images.img1_x_min + ((IMG1_CATHETUS + 1) * data->editor.images.column1 - 1),
        .y1 = data->editor.images.img_y_min + (IMG1_CATHETUS + 1), .y2 = data->editor.images.img_y_min + (IMG1_CATHETUS + 1)};
    //draw horizontal gridline
    while (row_temp > 1)
    {
        SDL_RenderDrawLine(data->gfx.renderer, grid.x1, grid.y1, grid.x2, grid.y2);
        grid.y1 = grid.y1 + (IMG1_CATHETUS + 1);
        grid.y2 = grid.y1;
        row_temp--;
    }
}

static void draw_rect(t_drown *data)
{
    SDL_Rect    element_fill;

    element_fill = (SDL_Rect){.x = data->editor.images.img1_x_min, .y = data->editor.images.img_y_min,
        .w = data->editor.images.column1 * (IMG1_CATHETUS + 1), .h = (data->editor.images.row1 * (IMG1_CATHETUS + 1))};
    SDL_SetRenderDrawColor(data->gfx.renderer, 0xFF, 0x99, 0x00, 0x00);
    SDL_RenderFillRect(data->gfx.renderer, &element_fill);
}

int img1_to_gui(t_drown *data)
{
/*  load a very transparent story-related background image */
    SDL_RenderClear(data->gfx.renderer);
    draw_rect(data);
    draw_grid(data);
    return (0);    
}
