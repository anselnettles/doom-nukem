/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:57 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/21 12:12:23 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

/*LIBRARIES.*/
# include <unistd.h>				/*UNIX Standard library.*/
# include <stdlib.h>				/*Standard library.*/
# include <fcntl.h>				/*File Control library.*/
# include "../libSDL2/include/SDL2/SDL.h"	/*Simple DirectMedia Layer.*/

/*GRAPHIC GLOBAL DEFINITIONS*/
# define TITLE "Bitter Cold Droplets in Autumn Rain | github.com/AnselNettles"
# define NAME "doom-nukem"	/*Rename when necessary.*/
# define WIDTH 640		/*Window resolution width.*/
# define HEIGHT 480		/*Window resolution height.*/
# define TOP_MARGIN 10		/*Top margin length for the UI.*/
# define MAP_MARGIN 460		/*Width margin distance for the map UI.*/

/*SYSTEM MECHANICS GLOBAL DEFINITIONS*/
# define RUN_GAME 1			// User request for running the game.
# define RUN_LEVEL_EDITOR 2		// User request for running the editor.
# define TRUE 1				// Set to true.
# define FALSE 0			// Set to false.
# define ERROR 1			// Reference to return value.
# define SCALE 1			// Resolution scale.
# define SDL_ERROR -1			// Reference to SDL function's return.
# define MAX 1000			// Irrelevant level size maximum.
# define ENDLESS 1			// SDL loop.
# define PLAYER_MAP 1			// Block map definition.
# define DEV_MAP 2			// Array map definition.

/*CONTROL MAPPING GLOBAL DEFINITIONS*/
# define ESC SDLK_ESCAPE		/*SDL Keysym definition for ESC.*/
# define NUMPAD_PLUS SDLK_PLUS		/*SDL Keysym definition for plus.*/
# define NUMPAD_MINUS SDLK_MINUS	/*SDL Keysym definition for minus.*/

//Map output color codes.
# define WALL 0xFF772E
# define SKY 0x004744
# define CEILING 0x11736E
# define PIT 0x364007
# define FLOOR 0x6f8410
# define EMPTY 0x171717
# define SLOT 0x303030 

//Terminal output color codes.
# define T_NUL "\033[0m"		// Default terminal type color.
# define T_ORANGE "\033[1;33m"		// Bold orange terminal type color.
# define T_ORANGES "\033[0;33m"		// A slim orange terminal type color.
# define T_RED "\033[0;31m"		// A red terminal type color.
# define T_LGRAY "\033[0;37m"		// A light gray terminal type color.

//System-wise variables for run and check-up calls through the two programs.
typedef struct s_system {
	int		user_request;
}	t_system;

//Editor-wise variables used mainly for resolving the level editor program.
typedef struct s_editor {
	char		*file;
	char		buffer[MAX + 1];
	char		array[MAX + 1][MAX + 1];
}	t_editor;

//Index-wise variables used for counts. Index 'i' is used for the level file's
//buffer string, while variables 'x' and 'y' are for the array of the extracted
//level.
typedef struct s_index {
	int			i;
	int			x;
	int			y;
	int			width;
}	t_index;

//Graphical-wise variables used for SDL.
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
	int				scale;
	int				map;
}	t_graph;

//We're making a mother of all structs here, Jack. Can't fret over every rule.
typedef struct s_rain {
	t_system	system;
	t_editor	editor;
	t_index		index;
	t_graph		graph;
}	t_rain;

// Listed error types
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

void	pixel_put(t_graph *g, int x_source, int y_source, int c);
void	sdl_loop(t_rain *rain);
void	*ft_memalloc(size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
#endif
