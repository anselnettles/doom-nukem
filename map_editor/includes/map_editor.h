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
    char                ***map;
    char                ***map_temp;        //remember to free
    //map coordinates referring x and y
    unsigned short int  map_x;
    unsigned short int  map_y;
    //img2: these convert into param_to_modify
    unsigned short int  param_x_to_modify;
    unsigned short int  param_y_to_modify;
    //img2: selected parameter type
    unsigned short int  param_to_modify;
    //img3: these convert into selection_index
    unsigned short int  selection_x;
    unsigned short int  selection_y; 
    //img3: selected index of a chosen parameter type
    unsigned short int  selection_index;
}   t_map;

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
    unsigned short int  img_switch;
    unsigned short int  row1;           //change names. row1 -->> img1_rows, column2 -->> img2_columns, ...
    unsigned short int  column1;
    unsigned short int  row2;
    unsigned short int  column2;
    unsigned short int  row3;
    unsigned short int  column3;        //keep this despite not used (grid3 is pre-defined as a column, x == 0)
}   t_editor_images;

typedef struct  s_character
{
    char    param0_choice0;
    char    param0_choice1;
    char    param0_choice2;
    char    param0_choice3;
    char    param0_choice4;
    char    param0_choice5;

    char    param1_choice0;
    char    param1_choice1;
    char    param1_choice2;
    char    param1_choice3;

    char    param2_choice0;
    char    param2_choice1;
    char    param2_choice2;

    char    param3_choice0;
    char    param3_choice1;
}   t_character;

typedef struct s_mouse
{
    int x;
    int y;
    int wheel_y;
}   t_mouse;

enum KeyPressSurfaces       //this will not be used in map editor
{
    KEYPRESS_SURFACE_DEFAULT,
    KEYPRESS_SURFACE_UP,
    KEYPRESS_SURFACE_DOWN,
    KEYPRESS_SURFACE_LEFT,
    KEYPRESS_SURFACE_RIGHT,
    KEYPRESS_SURFACE_TOTAL
};

/*  RENAMING
    get_m1_pressed_map_element  ->  img1_img2_is_mouse_in_grid()
    get_m1_pressed_img3_grid_element    ->  
    img1_and_img2   ->  
*/
void    choose_to_reset_map_or_exit(t_editor *editor, t_editor_images *images, t_mouse *mouse, t_map *data);
void    close_program(t_editor *editor);
void    create_map_temp(t_map *data, t_editor_images *images);
void    copy_map_to_map_temp(t_map *data, t_editor_images *images);
int     get_m1_pressed_img3_grid_element(t_mouse *mouse, t_map *data, t_editor_images *images);
int     get_m1_pressed_map_element(t_mouse *mouse, t_map *data, t_editor_images *images);
void    img1_and_img2(t_editor *editor, t_map *data, t_mouse *mouse, t_editor_images *images);
int     img1_to_gui(t_editor *editor, t_mouse *mouse, t_editor_images *images);
int     img2_to_gui(t_editor *editor, t_editor_images *images);
int     img3_to_gui(t_editor *editor, t_editor_images *images, t_map *data);
int     init(t_editor *editor);
int     map_editor(char *map_file, t_map *data);
void    param_to_modify(t_map *data);
void    read_map(char *map_file, t_map *data, t_editor_images *images);
//save_map();
void    select_new_param_value(t_editor *editor, t_map *data, t_character *chars, t_editor_images *images);
void    set_image_limits(t_editor_images *images);
void    set_values_for_parameters(t_character *chars);
void    tt_errors(char *error_msg);

//validate_map(buf);

/* below functions will be excluded from the final map_editor */
void    testing_print_map(t_map *data, t_editor_images *images);

#endif
