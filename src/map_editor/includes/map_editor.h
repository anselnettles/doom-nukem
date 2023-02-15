#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H
# include <stdio.h>             // remove
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>
# include "../SDL2/SDL.h"
# define BUF_SIZE 1500000
# define SCREEN_W 1280
# define SCREEN_H 800
# define IMG1_CATHETUS 12
# define IMG2_CATHETUS 36
# define IMG3_CATHETUS 48
# define IMG2_PARAM_COL 2
# define IMG2_PARAM_ROW 3
# define IMG3_PARAM_COL 1
# define PARAM_COUNT 5
# define ASCII_MIN 32
# define ASCII_MAX 127

typedef struct s_editor //
{
    SDL_Window      *window;
    SDL_Event       event;
    
    char            str_hex[11];            //not used, can replace str[11] with this
    uint32_t		texture[3][2][2];       //3, y and x size is to be re-defined here. See combined_final_format.txt
    uint32_t		weed[3][2][2];
    uint32_t        beginning[3][2][2];
    uint32_t        bad_end[3][2][2];
    uint32_t        good_end[3][2][2];
    uint32_t        bottle[3][2][2];
    uint32_t        ammo[3][2][2];
    uint32_t        right_arm[3][2][2];
    uint32_t        harpoon[6][2][2];
    uint32_t        goal[6][2][2];
    uint32_t        timer[3][2][2];
    uint32_t        left_arm[3][2][2];
    uint32_t        title_screen[2][2];
    uint32_t        foliage[2][2];
    uint32_t        moss[2][2];
    uint32_t        letters[2][2];
    uint32_t        skybox[2][2];

}   t_editor; // editor -> gfx

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
    unsigned short int	buffer_rows;
	unsigned short int	buffer_columns;
}   t_editor_images;

typedef struct  s_character
{
    char    param0_choice0;
    char    param0_choice1;
    char    param0_choice2;
    char    param0_choice3;
    char    param0_choice4;
    char    param0_choice5;
    char    param0_choice6;
    char    param0_choice7;
    char    param0_choice8;
    char    param0_choice9;
    //param1: texture
    char    param1_choice0;
    char    param1_choice1;
    char    param1_choice2;
    char    param1_choice3;
    //param2: 45 degree, x - y
    char    param2_choice0;
    char    param2_choice1;
    char    param2_choice2;
    char    param2_choice3;
    char    param2_choice4;
    //param3: entity
    char    param3_choice0;
    char    param3_choice1;
    char    param3_choice2;
    char    param3_choice3;
    char    param3_choice4;
    char    param3_choice5;
    char    param3_choice6;
    char    param3_choice7;
    //param4: secret
    char    param4_choice0;
    char    param4_choice1;
    char    param4_choice2;
}   t_character;

typedef struct s_index
{
    unsigned short int  i0;
    unsigned short int  i1;
    unsigned short int  i2;
}   t_index;

typedef struct s_mouse
{
    int x;
    int y;
    int wheel_y;
}   t_mouse;

/*  RENAMING
    img1_and_img2   ->  
*/
void        choose_to_reset_map_or_exit(t_editor *editor, t_editor_images *images, t_mouse *mouse, t_map *data);
void        close_program(t_editor *editor);
void        create_map_temp(t_map *data, t_editor_images *images);
void        copy_map_to_map_temp(t_map *data, t_editor_images *images);
int         img1_img2_is_mouse_in_grid(t_mouse *mouse, t_map *data, t_editor_images *images);
void        img1_and_img2(t_editor *editor, t_map *data, t_mouse *mouse, t_editor_images *images);
int         img1_to_gui(t_editor *editor, t_mouse *mouse, t_editor_images *images);
int         img2_to_gui(t_editor *editor, t_editor_images *images);
int         img3_is_mouse_in_grid(t_mouse *mouse, t_map *data, t_editor_images *images);
int         img3_to_gui(t_editor *editor, t_editor_images *images, t_map *data);
int         init(t_editor *editor);
void        initialization(t_editor_images *images, t_map *data, t_character *chars, char *map_file, t_editor *editor);
int         map_editor(char *map_file, t_map *data);
int         overwrite_map_file(t_map *data, t_editor_images *images);
void        param_to_modify(t_map *data);
void        parse_map_file_to_arrays(char *buf, t_editor *editor);
void        read_map(char *map_file, t_map *data, t_editor_images *images, t_editor *editor);
int         save_changes(t_editor *editor);
void        select_new_param_value(t_editor *editor, t_map *data, t_character *chars);
void        set_image_limits(t_editor_images *images);
void        set_values_for_parameters(t_character *chars);
uint32_t    swap_red_with_blue(uint32_t hex_value);
void        tt_errors(char *error_msg);
int         validate_buffer_format(char *buf, t_editor_images *images);
int         validate_map_temp(t_map *data, t_editor_images *images, t_character *chars);

/* below functions will be excluded from the final map_editor */
void    testing_print_map(t_map *data, t_editor_images *images);
#endif
