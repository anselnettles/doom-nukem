/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drowning.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:57 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/06 22:01:19 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DROWNING_H
# define DROWNING_H

//	LIBRARIES
# include <math.h>							// Math library.
# include <unistd.h>						//UNIX Standard library.
# include <fcntl.h>							//File Control library.
# include <pthread.h>
# include <SDL2/SDL.h>						//Simple DirectMedia Layer.
# include "../libft/libft.h"

# ifdef __APPLE__
#  include "SDL_image.h"
# elif __linux__
#  include <SDL2/SDL_image.h>
# endif

//	GRAPHIC GLOBAL DEFINITIONS
# define TITLE "Project Drowning | github.com/AnselNettles/doom-nukem"
# define NAME "doom-nukem"

# define WIDTH 642			//Window resolution width.
# define HEIGHT 480			//Window resolution height.
# define MARGIN 20			//Margin difference for the UI.
# define MAP_WIDTH 28		//Map grid width length.
# define MAP_HEIGHT 20		//Map grid height length.

//	SYSTEM MECHANICS GLOBAL DEFINITIONS
# define TRUE 1						//Set to true.
# define FALSE 0					//Set to false.
# define ERROR 1					//Reference to return value.
# define NEW_LINE 2					//Reference to file parser return value.
# define SDL_ERROR -1				//Reference to SDL function's return.
# define PI 3.1415927				//Topi's build.
# define SPEED 1					//Topi's build.
# define BITS 64					//Topi's build.
# define MMWIDTH 210				//Topi's build.
# define MMHEIGHT 100				//Topi's build.
# define LIMIT 100					//Topi's build.
# define THREAD 6					//Topi's build.
# define THREADRAY 142				//Topi's build.
# define EXIT 0						//Topi's build.
# define PLAY 1						//Topi's build.
# define RUN_EDITOR 2				//Reference for main function level editor.
# define GRAVITY 6.f
# define DEGREES 0.0174532
# define BAD_ENDING 1				//Player dies.
# define REGULAR_ENDING 2			//Player escapes.
# define GOOD_ENDING 3				//Player escapes and defeats the monster.

//	TERMINAL OUTPUT COLOR DEFINITIONS
# define T_NUL "\033[0m"				//Default terminal type color.
# define T_ORANGE "\033[1;33m"			//Bold orange terminal type color.
# define T_ORANGES "\033[0;33m"			//A slim orange terminal type color.
# define T_RED "\033[0;31m"				//A red terminal type color.
# define T_LGRAY "\033[0;37m"			//A light gray terminal type color.

//	SPRITE DIMENSIONS DEFINITIONS
# define FLOOR 0						//Floor texture. AKA. texture 'A'.
# define WALL_TEXTURE 1					//Wall texture. AKA. texture 'B'.
# define PILLAR_TEXTURE 2				//Pillar texture. AKA. texture 'C'.
# define CRATE 3						//Crate texture. AKA. texture 'D'.
# define TEXTURE_HEIGHT 64				//Standard texture height.
# define TEXTURE_WIDTH 64				//Standard texture width.
# define SKYBOX 4						//Skybox texture. AKA. texture 'E'.
# define SKYBOX_HEIGHT 480				//Skybox texture height.
# define SKYBOX_WIDTH 720				//Skybox texture width.
# define RIGHT_ARM 5					//Overlay right arm sprite. AKA. 'F'.
# define RIGHT_ARM_HEIGHT 250			//Right arm sprite height.
# define RIGHT_ARM_WIDTH 238			//Right arm sprite width.
# define LETTERS 6						//Overlay text script sprite. AKA. 'G'.
# define LETTERS_HEIGHT 20				//Text script sprite height.
# define LETTERS_WIDTH 728				//Text script sprite width.
# define LETTER_WIDTH 8					//Width of a single letter in sprite.
# define HARPOON 7						//Collectible harpoon sprite. AKA. 'H'.
# define BOTTLE 8						//Collectible bottle sprite. AKA. 'I'.
# define BOTTLE_WIDTH 38				//Bottle sprite width.
# define TIMER 9						//HUD timer background sprite. AKA. 'J'.
# define TIMER_HEIGHT 90				//HUD timer background sprite height.
# define TIMER_WIDTH 60					//HUD timer background sprite width.
# define BUBBLE 10						//HUD timer bubble sprite. AKA. 'K'.
# define BUBBLE_HEIGHT 12				//HUD timer bubble sprite height.
# define BUBBLE_WIDTH 12				//HUD timer bubble sprite width.
# define AMMO 11						//HUD ammo sprite. AKA. texture 'L'.
# define AMMO_HEIGHT 45					//HUD ammo sprite height.
# define AMMO_WIDTH 32					//HUD ammo sprite width.
# define MONSTER 12						//Monster sprites set. AKA. texture 'M'.
# define MONSTER_HEIGHT 128				//Monster sprites height.
# define MONSTER_WIDTH 128				//Monster spright width.
# define ALGAE 13						//Algae texture layer. AKA. texture 'N'.
# define CHAIN 14						//Goal point sprite. AKA. texture 'O'.
# define CHAIN_WIDTH 12					//Goal point sprite width.
# define TRANSITION 15					//Transition texture. AKA. texture 'P'.
# define TRANSITION_HEIGHT 48			//Transition texture height.
# define TRANSITION_WIDTH 642			//Transition texture width.

//	MAP EDITOR DEFINITIONS
# define IMG1_CATHETUS 12
# define IMG2_CATHETUS 80
# define IMG3_CATHETUS 70
# define IMG2_PARAM_COL 1
# define IMG2_PARAM_ROW 5
# define IMG3_PARAM_COL 1
# define PARAM_COUNT 5
# define ASCII_MIN 32
# define ASCII_MAX 127

//	System-wise variables for run and check-up calls through the program.
typedef struct s_system {
	int				play_state;
	int				user_request;
	int				ending_state;
	const uint8_t	*keyboard_state;
	uint32_t		time;
	uint32_t		last_time;
	uint32_t		delta_time;
	float			frame_time;
	uint32_t		second;
	uint32_t		five_second;
	int				overlay_toggle;
	int				filters;
	int				transition;
}	t_system;

typedef struct s_vector {
	int		x;
	int		y;
}	t_vector;

typedef struct s_vectorf {
	float	x;
	float	y;
}	t_vectorf;


typedef struct s_dda {
	t_vectorf	delta_dist;
	t_vectorf	step;
	t_vectorf	side_dist;
	int			hit;
	int			side;
}	t_dda;

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
    char    param0_choice10;
    char    param0_choice11;
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
    char    param4_choice3;
    char    param4_choice4;
}   t_character;

typedef struct s_mouse
{
    int x;
    int y;
}   t_mouse;

typedef struct s_xy_start_end
{
    int         x_start;
    int         x_end;
    int         y_start;
    int         y_end;
    uint32_t    colour;
}   t_xy_start_end; //interval

typedef struct s_editor
{
	t_editor_images images;
    t_character     chars;
	t_xy_start_end	interval;
	t_mouse			mouse;
}	t_editor;

//	Index-wise variables used for counts. Index 'i' is used for the level
//	file's buffer string, while variables 'x' and 'y' are for the array of
//	the extracted level. Variable 'p' stands for the map's third dimension:
//	environmental parameters within the XY location.
typedef struct s_index {
	int				i;
	int				x;
	int				y;
	int				p; //[y][x][p]
	int				f;
	int				width;
	int				hex_count;
	int				hex_step;
	//from map editor s_index
	unsigned short int  i0;
    unsigned short int  i1;
    unsigned short int  i2;
}	t_index;

//	Player location and movement structure. Mother to collision struct.
typedef struct s_player {
	t_vectorf		velocity;
	float			base_height;
	float			x;
	float			y;
	float			dir;
	float			dx;
	float			dy;
	int				in_air;
	int				altitude;
	float			height;
	int				flag;
}	t_player;

// Wall location coordinates & trigonometric values.
typedef struct s_wall {
	float		x;
	float		y;
	float		dir;
	float		dx;
	float		dy;
	float		distance;
	int			prev_y;
	char		*lock;
	int			side;
}	t_wall;

typedef struct s_animation {
	uint32_t	right_arm;
	uint32_t	timer;
	uint32_t	bubble;
	uint32_t	ammo;
	uint32_t	bottle;
	uint32_t	algae;
	uint32_t	transition;
}	t_frame;

typedef struct s_image {
	uint32_t	*pixels;
	int	width;
	int	height;
}	t_image;

typedef struct s_texture {
	t_image	frame[10];
	int	frame_count;
}	t_texture;

//	Graphical-wise variables used for SDL and graphical drawing.
//	Mother to raycast struct.
typedef struct s_graphics {
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Surface		*image;
	float			proj_dist;
	const char		*sdl_error_string;
	int				width;
	int				height;
	int				f;
	int				x;
	int				y;
	int				centre;
	uint32_t		color;
	int				scale;
	float			shake_x;
	float			shake_y;
	int				shake_xtoggle;
	int				shake_ytoggle;
	int				flow_y_adjust;
	t_texture		texture[16];
	t_frame			frame;
	SDL_Event		event;
}	t_gfx;

typedef struct s_map
{
	int					y_max;				//remove if topi does not use these
	int					x_max;				//remove if topi does not use these
    char                ***map;
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
}	t_map;

typedef struct s_map_grid	//remove if not needed in final GUI, was part of render functions
{
    int x1;
    int x2;
    int y1;
    int y2;
}   t_map_grid;


typedef struct s_ray
{
	t_gfx		gfx;
	t_player	player;
	t_map		map;
	float		distance;
	float		dir;
	int			x;
	int			count;
	int			height;
}	t_ray;

//	Mother structure.
typedef struct s_project_drowning {
	t_system				system;
	t_index					index;
	t_editor				editor;
	t_player				player;
	t_gfx					gfx;
	SDL_Rect				rect;
	SDL_Event				event;
	t_map					map;
	float					delta_time;
}	t_drown;

//	Listed error types. See 'error_management.c' for their output.
typedef enum e_error
{
	BAD_ARGS,
	NO_FILE,
	BAD_FILENAME,
	OPEN_FAIL,
	READ_FAIL,
	FILE_MAX,
	CLOSE_FAIL,
	PARSE_FAIL,
	MALLOC_FAIL,
	BAD_WALL,
	EDITOR_FAIL,
	SDL_FAIL,
	PLAYER_FAIL,
	RENDER_FAIL,
	TEXTURE_FAIL,
	OVERLAY_ERROR,
	GFX_WRITE_ERROR,
}	t_error;


//	Non-static functions.
int			animation_loop(t_drown *d);
void		choose_to_reset_map_or_exit(t_drown *data);
void    	clear_surface(t_drown *data);
void		close_program(t_gfx *gfx);
void		collect_airbottle(t_drown *d);
char		*copy_line(char *line, t_map *data);
void		deal_key(int key, t_drown *data);
void		deal_mouse(t_drown *data);
void		delta_move_player(t_drown *data);
void		delta_time_move(t_drown *data);
void		draw_ceiling(t_ray *ray, t_wall wall, int win_y);
void		draw_collumn(t_ray *ray, int y, int y_max, Uint32 color);
void		draw_color_filter(t_gfx *gfx);
void		draw_floor(t_ray *ray, t_wall wall, int win_y);
void    	draw_grid_of_squares(t_drown *data);
void		draw_map(t_drown *data);
void		draw_one_square(t_gfx *gfx, t_xy_start_end *interval);
void		draw_scanlines(t_gfx *gfx);
void		draw_texture(t_ray *ray, int y, int y_max, t_wall wall, float distance, int	scaled_y, int wall_layer);
void		draw_thread(t_ray *ray, float distance, t_wall *wall);
int			editor_pix_put(t_gfx *gfx, int x, int y, uint32_t colour);
uint32_t   	element_colour(t_map *map, int row_now, int col_now, int image_switch);
int			error(int code);
void		fill_gaps(char *line);
void		*ft_raycast_thread(void  *args);
int			gfx_write(t_gfx *gfx, char *str);
uint32_t	fade_brightness(uint32_t color, int multiplier);
void		img1_and_img2(t_drown *data); //rename
int			img1_img2_is_mouse_in_grid(t_drown *data);
int			img3_is_mouse_in_grid(t_drown *data);
void		init_player(t_player *player);
int			init_sdl(SDL_Window *window, SDL_Surface *screen);
int			init(t_gfx *gfx);
int			is_element_bloated(t_map *map, t_editor_images *images);
int			map_editor(char *map_file, t_drown *data);
void		map_len(char *file, t_map *data);
int			memory_allocate_textures(t_gfx *gfx, int f);
void		move_forward_back(t_drown *data);
void		move_strafe(t_drown *data);
void		param_to_modify(t_map *map);
int			pixel_put(t_gfx *gfx, int x_src, int y_src, uint32_t color);
int			read_map(char *map_file, t_drown *data);
int			render_hud(t_index *index, t_gfx *gfx, int scale);
int			render_overlay(t_drown *d);
int			render(t_drown *d);
void		render_thread(t_drown *data);
void		right_arm_loop(t_drown *d);
void		rotate_player(int key, t_player *player);
void		scale_window(t_gfx *gfx);
void		sdl_loop(t_drown *drown);
void		select_new_param_value(t_drown *data);
void		set_image_limits(t_drown *data);
void		set_values_for_parameters(t_character *chars);
int			string_timeline(t_drown *d);
uint32_t	swap_red_with_blue(uint32_t hex_value);
int			texture_allocation(char *buf, t_index *i, t_gfx *gfx);
void		tt_errors(char *error_msg);
int			validate_buffer_format(char *buf, t_editor_images *images);
int			validate_map(t_drown *data);
int			validate_outer_walls(t_map *map, t_editor_images *images);
void		x_right_arm_flail(t_gfx *gfx);
void		y_right_arm_flail(t_gfx *gfx);
int			ft_calc_diagonal(t_wall *wall, t_ray *ray);
int			ft_diagonal_1(t_wall *wall, t_ray *ray);
int			ft_diagonal_2(t_wall *wall, t_ray *ray);
int			ft_diagonal_3(t_wall *wall, t_ray *ray);
int			ft_diagonal_4(t_wall *wall, t_ray *ray);
void		crouch(t_drown *data);
void		init_dda(t_ray *ray, t_wall *wall, t_dda *dda);
void   		algo_dda(t_ray *ray, t_wall *wall, t_dda *dda);
void		flow_adjustment(t_drown *d);
void		overworld_sprite_loop(t_drown *d);
void		hud_animation_loop(t_drown *d);

//dont remove before final build. it is used to test if map values are changed correctly
void    	testing_print_map(t_drown *data, t_editor_images *images);
#endif
