#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../SDL2/SDL.h"
# define BUF_SIZE 50000
# define SCREEN_W 1280
# define SCREEN_H 800
# define IMG1_CATHETUS 12
# define IMG2_CATHETUS 36
# define IMG3_CATHETUS 48
# define IMG2_PARAM_COL 2
# define IMG2_PARAM_ROW 2
# define IMG3_PARAM_COL 1
// # define IMG3_PARAM_ROW 5    /* this cannot be a fixed value, see render_img3_based_on_param.c */
# define PARAM_COUNT 4


typedef struct s_editor
{
    SDL_Window      *window;
    SDL_Renderer    *renderer;
    SDL_Surface     *ScreenSurface;
    SDL_Event       event;
}   t_editor;

typedef struct s_map
{
    char    ***map;
    int     x_to_modify;
    int     y_to_modify;
    int     param_x_to_modify;
    int     param_y_to_modify;
    int     param_to_modify;
}   t_map;

/*  if mallocing map as struct, need to convert map to 4D (****map)*/
// typedef struct s_map_parameter
// {
//     short int   floor_height;
//     Uint8       transparency;
//     char        *wall_texture;
//     char        entity;
// }    t_map_parameter;

typedef struct s_map_grid
{
    int x1;
    int x2;
    int y1;
    int y2;
}   t_map_grid;

typedef struct s_editor_images
{
    unsigned short int  img1_x_min;
    unsigned short int  img1_x_max;
    unsigned short int  img2_x_min;
    unsigned short int  img2_x_max;
    unsigned short int  img3_x_min;
    unsigned short int  img3_x_max;
    unsigned short int  img_y_min;
    unsigned short int  img_y_max;
    unsigned short int  map_x;
    unsigned short int  map_y;
    unsigned short int  selection_index;
    unsigned short int  img_switch;
    unsigned short int  row1;
    unsigned short int  column1;
    unsigned short int  row2;
    unsigned short int  column2;
    unsigned short int  row3;
    unsigned short int  column3;

}   t_editor_images;

typedef struct s_mouse
{
    int x;
    int y;
    int wheel_y;
}   t_mouse;

enum KeyPressSurfaces
{
    KEYPRESS_SURFACE_DEFAULT,
    KEYPRESS_SURFACE_UP,
    KEYPRESS_SURFACE_DOWN,
    KEYPRESS_SURFACE_LEFT,
    KEYPRESS_SURFACE_RIGHT,
    KEYPRESS_SURFACE_TOTAL
};

//validate_map(buf);
//save_map();
void    set_image_limits(t_editor_images *lim);
int     map_editor(char *map_file, t_map *dimensions);
void    tt_errors(char *error_msg);
void    read_map(char *map_file, t_map *dimensions, t_editor_images *lim);
int     img1_to_gui(t_editor *editor, t_mouse *mouse, t_editor_images *lim);
int     img2_to_gui(t_editor *editor, t_editor_images *lim);
int     img3_to_gui(t_editor *editor, t_editor_images *lim, t_map *dimensions);
int     get_m1_pressed_map_element(t_mouse *mouse, t_map *dimensions, t_editor_images *lim);
void    close_program(t_editor *editor);
int     init(t_editor *editor);
void    param_to_modify(t_map *dimensions);
void    img1_and_img2(t_editor *editor, t_map *dimensions, t_mouse *mouse, t_editor_images *lim);
int     get_m1_pressed_img3_grid_element(t_mouse *mouse, t_map *dimensions, t_editor_images *lim);

/* below functions will be excluded from the final map_editor */
void    testing_print_map(t_map dimensions, t_editor_images lim);

#endif
