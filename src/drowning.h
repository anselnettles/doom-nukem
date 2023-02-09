/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drowning.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:57 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/09 13:28:54 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DROWNING_H
# define DROWNING_H

//	LIBRARIES
# include <stdio.h>							//Standard input output.
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

//	SYSTEM MECHANICS GLOBAL DEFINITIONS
# define TRUE 1						//Set to true.
# define FALSE 0					//Set to false.
# define ERROR 1					//Reference to return value.
# define NEW_LINE 2					//Reference to file parser return value.
# define SDL_ERROR -1				//Reference to SDL function's return.
//# define BUFFER_MAX 2550			//Level file maximum size.
//# define MAX 50						//Map array dimension maximum.
//# define PARAMS 10					//Map array parameter dimension maximum.
//# define MAP_WIDTH 50				//Level map line width.
//# define HORIZONTAL 1				// A toggle variable for raycast calculation
//# define VERTICAL 0					// A toggle variable for raycast calculation
//# define PLAYER_MAP 1				//Block map definition when rendering map.
//# define DEV_MAP 2					//Array map definition when rendering map.
//# define FOV 40						//Field of vision.
//# define SQUARE_SIZE 64				//Size of a side of a terrain block.
//# define MOVE_SPEED 8				//Player's movement speed.
//# define RAY_LENGTH 3				//Length of a cast ray.
//# define TURN_SPEED 4				//Player's turning speed.
# define PI 3.1415927				//Topi's build.
# define SPEED 10					//Topi's build.
# define BITS 64					//Topi's build.
# define MMWIDTH 210				//Topi's build.
# define MMHEIGHT 100				//Topi's build.
# define LIMIT 100					//Topi's build.
# define THREAD 6					//Topi's build.
# define THREADRAY 142				//Topi's build.
# define EXIT 0						//Topi's build.
# define PLAY 1						//Topi's build.
//# define DEGREE 0.0174532
# define DEGREES 0.0174532
//# define NORTH 1					//Reference to wall texture direction.
//# define EAST 2
//# define SOUTH 3
//# define WEST 4

//	TERMINAL OUTPUT COLOR DEFINITIONS
# define T_NUL "\033[0m"				//Default terminal type color.
# define T_ORANGE "\033[1;33m"			//Bold orange terminal type color.
# define T_ORANGES "\033[0;33m"			//A slim orange terminal type color.
# define T_RED "\033[0;31m"				//A red terminal type color.
# define T_LGRAY "\033[0;37m"			//A light gray terminal type color.

//	System-wise variables for run and check-up calls through the program.
typedef struct s_system {
	int				play_state;
	int				user_request;
	const uint8_t			*keyboard_state;
	uint32_t		time;
	uint32_t		last_time;
	uint32_t		delta_time;
	uint32_t		second;
}	t_system;

//	Editor-wise variables used mainly for resolving the level editor program.
typedef struct s_editor {
//	char			*file;
//	char			buffer[BUFFER_MAX + 1];
//	char			map[MAX + 1][MAX + 1][PARAMS + 1];
//	int				start_x;
//	int				start_y;
}	t_editor;

//	Index-wise variables used for counts. Index 'i' is used for the level
//	file's buffer string, while variables 'x' and 'y' are for the array of
//	the extracted level. Variable 'p' stands for the map's third dimension:
//	environmental parameters within the XY location.
typedef struct s_index {
	int				i;
	int				x;
	int				y;
	int				p;
	int				width;
}	t_index;
/*
//	A middle-man coordination variables in double format.
typedef struct s_coordinate_double {
	double			x;
	double			y;
}	t_corf;

typedef struct s_location_double {
	double			start_x;
	double			end_x;
	double			start_y;
	double			end_y;
	int				y;
	int				y1;
	int				y2;
}	t_location;

//	Collision handling variables, stored within the player structure.
typedef struct s_collision_detection {
	int				x;
	int				x_pos_offset;
	int				x_neg_offset;
	int				y;
	int				y_pos_offset;
	int				y_neg_offset;
}	t_collide;*/

//	Player location and movement structure. Mother to collision struct.
typedef struct s_player {
//	float			pos_angle;
//	float			pos_x;
//	float			pos_y;
//	float			dir_x;
//	float			dir_y;
//	int				move_speed;
//	int				compass;
//	t_collide		collide;

	float			x;
	float			y;
	float			dir;
	float			dx;
	float			dy;
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
}	t_wall;

typedef struct s_animations {
	uint32_t	right_arm;
}	t_frame;

typedef struct	s_sprites {
	uint32_t	right_arm[3][238][250];
}	t_sprite;

typedef struct s_textures {
	uint32_t	texture_a[64][64];
	uint32_t	texture_b[64][64];
	uint32_t	texture_c[64][64];
	uint32_t	textire_d[64][64];
	uint32_t	skybox[64][128];
}	t_txt;

//	Graphical-wise variables used for SDL and graphical drawing.
//	Mother to raycast struct.
typedef struct s_graphics {
	SDL_Window		*window;
	SDL_Surface		*screen;
	SDL_Surface		*image;
	float			dop;		//distance to projection plane
	const char		*sdl_error_string;
	int				width;
	int				height;
	int				f;
	int				x;
	int				y;
	uint32_t			color;
	int				scale;
	float				shake_x;
	float				shake_y;
	int				shake_xtoggle;
	int				shake_ytoggle;
//	int				map;
	int				scanline;
	int				overlay_toggle;
	t_txt			txt;
	t_sprite		sprite;
	t_frame			frame;
}	t_gfx;

typedef struct s_map
{
	char	**map;
	int		y_max;
	int		x_max;
}	t_map;

//typedef struct s_texture
//{
//	Uint32	texture[64][64];
//}	t_texture;

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
	t_editor				editor;
	t_index					index;
	t_player				player;
	t_gfx					gfx;
	SDL_Rect				rect;
	SDL_Event				event;
	t_map					map;
	int						hg;
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
	BAD_SYMBOL,
	BAD_WIDTH,
	BAD_WALL,
	EDITOR_FAIL,
	SDL_FAIL,
	PLAYER_FAIL,
	RENDER_FAIL,
	TEXTURE_FAIL,
	OVERLAY_ERROR,
}	t_error;

//	Non-static functions'.
int			main(void);
int			read_file(t_drown *drown);
//int		buffer_to_map(char b[MAX + 1], t_editor *e, t_index *i, int width);
int			render(t_drown *d);
//int		raycast(t_drown *d, float hor_coll_dist, float ver_coll_dist);
//void		raycast_angle_check(t_gfx *g);
void		draw_minimap_slot(t_drown *d);
int			render_overlay(t_drown *d);
int			animation_loop(t_drown *d);
void		x_right_arm_flail(t_gfx *gfx);
void		y_right_arm_flail(t_gfx *gfx);
//void		print_array(t_editor *editor, t_index *index);

void		keyboard_input(t_drown *d);
//void		move_forward_back(t_editor *editor, t_player *p, SDL_Keycode key);
//void		move_turn(t_player *p, SDL_Keycode key);
void		scale_window(t_gfx *gfx);

//SDL_Surface	*img_load(char *path);
int			pixel_put(t_gfx *gfx, int x_src, int y_src, uint32_t color);
//void		vline(t_drown *d, t_location lo, float y, uint32_t color);

//float		square_root(float nb);
//int			max(int a, int b);
//int			min(int a, int b);
//int			clamp(int a, int lower, int upper);
//double		deg_to_rad(double degrees);

int			error(int code);

void		sdl_loop(t_drown *drown);

//Topi's build.
void	map_len(char *file, t_map *data);
char	*copy_line(char *line, t_map *data);
void	fill_gaps(char *line);
void	read_map(char *file, t_map *data);
int		init_sdl(SDL_Window *window, SDL_Surface *screen);
void	draw_map(t_drown *data);
void	init_player(t_player *player);
void	move_player(t_drown *data);
void	rotate_player(int key, t_player *player);
void	deal_key(int key, t_drown *data);
void	deal_mouse(t_drown *data);
void    render_thread(t_drown *data);
void	*ft_raycast_thread(void  *args);
void	strife(t_drown *data);
void	draw_thread(t_ray *ray, float distance, t_wall *wall);
void	draw_collumn(t_ray *ray, int y, int y_max, Uint32 color);
void	draw_texture(t_ray *ray, int y, int y_max, t_wall wall, int texture_y);
void	draw_floor(t_ray *ray, t_wall wall, int win_y);
void	draw_ceiling(t_ray *ray, t_wall wall, int win_y);

//To be removed
void	sprite_right_arm(t_drown *d);
void	texture_a_temp(t_drown *d);

#endif
