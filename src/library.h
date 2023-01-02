/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:57 by aviholai          #+#    #+#             */
/*   Updated: 2022/12/28 10:02:46 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

/*LIBRARIES.*/
# include <unistd.h>						/*UNIX Standard library.*/
# include <stdlib.h>						/*Standard library.*/
# include <fcntl.h>							/*File Control library.*/
# include "../libSDL2/include/SDL2/SDL.h"	/*Simple DirectMedia Layer.*/

/*GRAPHIC GLOBAL DEFINITIONS*/
# define TITLE "Bitter Cold Droplets in Autumn Rain | github.com/AnselNettles"
# define NAME "doom-nukem"			/*Rename when necessary.*/
# define WIDTH 640					/*Window resolution width.*/
# define HEIGHT 480					/*Window resolution height.*/
# define TOP_MARGIN 10				/*Top margin length for the UI.*/
# define MAP_MARGIN 460				/*Width margin distance for the map UI.*/

/*SYSTEM MECHANICS GLOBAL DEFINITIONS*/
# define RUN_GAME 1				/*User request for running the game.*/
# define RUN_LEVEL_EDITOR 2		/*User request for running the editor.*/
# define TRUE 1					/*Set to true.*/
# define FALSE 0				/*Set to false.*/
# define ERROR 1				/*Reference to return value.*/
# define SCALE 1				/*Resolution scale.*/
# define SDL_ERROR -1			/*Reference to SDL function's return.*/
# define MAX 1000				/*Irrelevant level size maximum.*/
# define ENDLESS 1				/*SDL loop.*/
# define PLAYER_MAP 1			/*Block map definition.*/
# define DEV_MAP 2				/*Array map definition.*/

/*CONTROL MAPPING GLOBAL DEFINITIONS*/
# define ESC SDLK_ESCAPE			/*SDL Keysym definition for ESC.*/
# define NUMPAD_PLUS SDLK_PLUS		/*SDL Keysym definition for plus.*/
# define NUMPAD_MINUS SDLK_MINUS	/*SDL Keysym definition for minus.*/

//New implementation defines
# define CEILING_TEXTURE 0x01315a
# define WALL_TEXTURE 0x345625
# define FLOOR_TEXTURE 0x979d53

# define FOV 60
# define SQUARE_SIZE 64
# define MOVE_SPEED 4;
# define RAY_LENGTH 3
# define TURN_SPEED 3
# define DEGREE 0.0174533
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4

/*
# define EYE_HEIGHT 6
# define DUCK_HEIGHT 2.5
# define HEAD_MARGIN 1
# define KNEE_HEIGHT 2
# define HOR_FOV 0.73f
# define VER_FOV 0.2f
*/

/*ARRAY MAP COLOR DEFINITIONS*/
# define WALL 0xFF772E
# define SKY 0x004744
# define CEILING 0x11736E
# define PIT 0x364007
# define FLOOR 0x6f8410
# define EMPTY 0x171717
# define SLOT 0x303030 

/*TERMINAL OUTPUT COLOR DEFINITIONS*/
# define T_NUL "\033[0m"			/*Default terminal type color.*/
# define T_ORANGE "\033[1;33m"		/*Bold orange terminal type color.*/
# define T_ORANGES "\033[0;33m"		/*A slim orange terminal type color.*/
# define T_RED "\033[0;31m"			/*A red terminal type color.*/
# define T_LGRAY "\033[0;37m"		/*A light gray terminal type color.*/

/*System-wise variables for run and check-up calls through the two programs.*/
typedef struct s_system {
	int		user_request;
}	t_system;

/*Editor-wise variables used mainly for resolving the level editor program.*/
typedef struct s_editor {
	char		*file;
	char		buffer[MAX + 1];
	char		array[MAX + 1][MAX + 1];
	int		start_x;
	int		start_y;
}	t_editor;

typedef struct s_stage {
	char		grid[MAX + 1][MAX + 1];
}	t_stage;

/*Index-wise variables used for counts. Index 'i' is used for the level file's
buffer string, while variables 'x' and 'y' are for the array of the extracted
level.*/
typedef struct s_index {
	int			i;
	int			x;
	int			y;
	int			width;
}	t_index;

typedef struct s_pointd
{
	double	x;
	double	y;
}	t_pointd;

typedef struct s_collision
{
	int	grid_pos_x;
	int	grid_pos_x_plus_offset;
	int	grid_pos_x_minus_offset;
	int	grid_pos_y;
	int	grid_pos_y_plus_offset;
	int	grid_pos_y_minus_offset;
}	t_collision;

/*Player location struct.*/
typedef struct s_player {
	struct	s_xyz {
		float	x;
		float	y;
		float	z;
	} where, velocity;
	float			angle;
	float			anglesin;
	float			anglecos;
	float			yaw;
	unsigned int	sector;

	t_collision		collision;
	double			pos_angle;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	int				move_speed;
	int				compass;
}	t_player;

typedef struct s_raycast
{
	double	ray_angle;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	offset_x;
	double	offset_y;
	double	dist_to_proj_plane;
	double	degrees_per_column;
	double	degrees_per_ray;
	double	hor_coll_point_x;
	double	ver_coll_point_y;
	double	closest_coll_dist;
	int		projected_slice_height;
	int		wall_texture_xoffset;
	int		wall_texture_yoffset;
	double	wall_texture_yincrement;
}	t_raycast;

/*Graphical-wise variables used for SDL and graphical drawing.*/
typedef struct s_graph {
	SDL_Event		e;
	SDL_Window		*win;
	SDL_Surface		*surf;
	const char		*sdl_error_string;
	int				width;
	int				height;
	int				x;
	int				y;
	uint32_t		color;
	uint32_t		top_color;
	uint32_t		middle_color;
	uint32_t		bottom_color;
	int				scale;
	int				map;
	t_raycast		raycast;
}	t_graph;

typedef struct s_intersect {
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		x3;
	int		y3;
	int		x4;
	int		y4;
}	t_intersect;

/*
//Sectors: Areas of floor and ceiling and listing of applied edges and neighbor.
typedef struct s_sector {
	float			floor;
	float			ceiling;
	struct s_xy {
		float	x;
		float	y;
	} *vertex;
	signed char		*neighbours;
	unsigned int	npoints;
}	t_sector;
*/

/*Mother struct*/
typedef struct s_rain {
	t_system		system;
	t_editor		editor;
	t_stage			stage;
	t_index			index;
	t_player		player;
	t_graph			graph;
	t_intersect		intersect;
//	t_sector		sector;
	t_pointd		pointd;
//	t_collision		collision;
//	t_raycast		raycast;
}	t_rain;

/*Listed error types*/
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
	EDITOR_FAIL,
	SDL_FAIL,
	RENDER_FAIL,
}	t_error;

int		error(int code);
int		main(int argc, char **argv);
int		read_file(t_rain *rain);
int		editor_sequence(t_rain *rain);
int		graphic_interface(t_rain *rain);
int		render(t_rain *r);
int		draw_map_slot(t_rain *r, int x, int y);
void	print_array(t_editor *editor, t_index *index);

void	keyboard(t_rain *r);

void	pixel_put(t_graph *g, int x_source, int y_source, int colour);
void	vline(t_graph *g, int x_source, int y_source1, int y_source2);
void	sdl_loop(t_rain *rain);
//int		overlap(int a0, int a1, int b0, int b1);
//int		vxs(int x0, int y0, int x1, int y1);
int		max(int a, int b);
int		min(int a, int b);
int		clamp(int a, int lower, int upper);
double	deg_to_rad(double degrees);
void	intersect(t_intersect *i);
void	*ft_memalloc(size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
#endif
