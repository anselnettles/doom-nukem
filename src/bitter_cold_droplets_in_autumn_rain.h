/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitter_cold_droplets_in_autumn_rain.h              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:57 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/26 15:33:32 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITTER_COLD_DROPLETS_IN_AUTUMN_RAIN_H
# define BITTER_COLD_DROPLETS_IN_AUTUMN_RAIN_H

//	LIBRARIES
# include <unistd.h>						//UNIX Standard library.
# include <fcntl.h>							//File Control library.
# include <SDL2/SDL.h>						//Simple DirectMedia Layer.
# include <stdio.h>

# ifdef __APPLE__
#  include "SDL_image.h"
# elif __linux__
#  include <SDL2/SDL_image.h>
# endif

//	GRAPHIC GLOBAL DEFINITIONS
# define TITLE "Bitter Cold Droplets in Autumn Rain | github.com/AnselNettles"
# define NAME "doom-nukem"

# define WIDTH 640					//Window resolution width.
# define HEIGHT 480					//Window resolution height.
# define TOP_MARGIN 10				//Top margin length for the UI.
# define MAP_MARGIN 460				//Width margin distance for the map UI.

//	SYSTEM MECHANICS GLOBAL DEFINITIONS
# define RUN_GAME 1					//User request for running the game.
# define RUN_LEVEL_EDITOR 2			//User request for running the editor.
# define TRUE 1						//Set to true.
# define FALSE 0					//Set to false.
# define ERROR 1					//Reference to return value.
# define NEW_LINE 2					//Reference to file parser return value.
# define SDL_ERROR -1				//Reference to SDL function's return.
# define ENDLESS 1					//Reference to an endless SDL while loop.
# define SCALE 1					//Resolution scale.
# define BUFFER_MAX 2550			//Level file maximum size.
# define MAX 50						//Map array dimension maximum.
# define PARAMS 10					//Map array parameter dimension maximum.
# define MAP_WIDTH 50				//Level map line width.
# define HORIZONTAL 1				// A toggle variable for raycast calculation
# define VERTICAL 0					// A toggle variable for raycast calculation
# define PLAYER_MAP 1				//Block map definition when rendering map.
# define DEV_MAP 2					//Array map definition when rendering map.
# define FOV 40						//Field of vision.
# define SQUARE_SIZE 64				//Size of a side of a terrain block.
# define MOVE_SPEED 8				//Player's movement speed.
# define RAY_LENGTH 3				//Length of a cast ray.
# define TURN_SPEED 4				//Player's turning speed.
# define DEGREE 0.0174533
# define NORTH 1					//Reference to wall texture direction.
# define EAST 2
# define SOUTH 3
# define WEST 4

//	GRAPHICAL RENDER COLOR DEFINITIONS
# define SKY_PRINT 0xad6f43			//Default color for sky.
# define FLOOR_PRINT 0x37352f		//Default color for floor.
# define BLUE_OUTLINE 0x042b49		//Color for vertical line border.
# define BROWN_OUTLINE 0x593e1c		//Color for vertical line border.

//	PLAYER MAP COLOR DEFINITIONS
# define WALL 0xFF772E
# define SKY 0x004744
# define CEILING 0x11736E
# define PIT 0x364007
# define FLOOR 0x6f8410
# define EMPTY 0x171717
# define START_POINT 0x8aad34
# define SLOT 0x303030 

//	TERMINAL OUTPUT COLOR DEFINITIONS
# define T_NUL "\033[0m"				//Default terminal type color.
# define T_ORANGE "\033[1;33m"			//Bold orange terminal type color.
# define T_ORANGES "\033[0;33m"			//A slim orange terminal type color.
# define T_RED "\033[0;31m"				//A red terminal type color.
# define T_LGRAY "\033[0;37m"			//A light gray terminal type color.

//	System-wise variables for run and check-up calls through the program.
typedef struct s_system {
	int				user_request;
}	t_system;

//	Editor-wise variables used mainly for resolving the level editor program.
typedef struct s_editor {
	char			*file;
	char			buffer[BUFFER_MAX + 1];
	char			map[MAX + 1][MAX + 1][PARAMS + 1];
	int				start_x;
	int				start_y;
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
}	t_collide;

//	Player location and movement structure. Mother to collision struct.
typedef struct s_player {
	float			pos_angle;
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	int				move_speed;
	int				compass;
	t_collide		collide;
}	t_player;

//	Raycast handling variables, stored within the graph structure.
typedef struct s_raycast {
	double	ray_angle;
	double	ray_x;
	double	ray_y;
	int		mapx;
	int		mapy;
	double	offset_x;
	double	offset_y;
	double	plane_dist;
	double	degrees_per_column;
	double	degrees_per_ray;
	double	hor_coll_point_x;
	double	ver_coll_point_y;
	double	closest_coll;
	int		slice_height;
	int		texture_xoffset;
	int		texture_yoffset;
	double	texture_yincrement;
}	t_cast;

//	Graphical-wise variables used for SDL and graphical drawing.
//	Mother to raycast struct.
typedef struct s_graphical {
	SDL_Event		e;
	SDL_Window		*win;
	SDL_Surface		*surf;
	SDL_Surface		*texture[4];
	const char		*sdl_error_string;
	int				width;
	int				height;
	int				x;
	int				y;
	uint32_t		color;
	int				scale;
	int				map;
	int				scanline;
	t_cast			cast;
}	t_graph;

//	Mother structure.
typedef struct s_bitter_cold_droplets_in_autumn_rain {
	t_system				system;
	t_editor				editor;
	t_index					index;
	t_player				player;
	t_graph					graph;
	t_corf					corf;
	t_location				loca;
	t_collide				collide;
}	t_rain;

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
}	t_error;

//	Non-static functions'.
int			main(int argc, char **argv);
int			read_file(t_rain *rain);
int			buffer_to_map(char b[MAX + 1], t_editor *e, t_index *i, int width);
int			graphic_interface(t_rain *rain);
int			render(t_rain *r);
int			raycast(t_rain *r, float hor_coll_dist, float ver_coll_dist);
void		raycast_angle_check(t_graph *g);
void		draw_minimap_slot(t_rain *r);
void		draw_overlay(t_rain *r);
void		print_array(t_editor *editor, t_index *index);

void		keyboard_input(t_rain *r);
void		move_forward_back(t_editor *editor, t_player *p, SDL_Keycode key);
void		move_turn(t_player *p, SDL_Keycode key);

SDL_Surface	*img_load(char *path);
void		pixel_put(t_graph *g, int x_src, int y_src, uint32_t color);
void		vline(t_rain *r, t_location lo, float y, uint32_t color);

float		square_root(float nb);
int			max(int a, int b);
int			min(int a, int b);
int			clamp(int a, int lower, int upper);
double		deg_to_rad(double degrees);

int			error(int code);

void		*ft_memalloc(size_t size);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
size_t		ft_strlen(const char *s);
void		sdl_loop(t_rain *rain);
#endif
