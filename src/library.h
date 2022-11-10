/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:57 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 12:19:25 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRARY_H
# define LIBRARY_H

# include <unistd.h>						// UNIX Standard library.
# include <stdlib.h>						// Standard library.
# include <fcntl.h>							// File Control library.
# include "../libSDL2/include/SDL2/SDL.h"	// Simple DirectMedia Layer library.

// Graphic window definitions.
# define TITLE "Bitter Cold Droplets in Autumn Rain | github.com/AnselNettles"
# define NAME "doom-nukem"				// Rename when necessary.
# define WIDTH 640						// Window resolution width.
# define HEIGHT 480						// Window resolution height.

//System-wise global definitions.
# define RUN_GAME 1						// User request for running the game.
# define RUN_LEVEL_EDITOR 2				// User request for running the editor.
# define TRUE 1							// Set to true.
# define FALSE 0						// Set to false.
# define ERROR 1						// Reference to return value.
# define SDL_ERROR -1					// Reference to SDL function's return.
# define MAX_READ 1000					// Irrelevant level size maximum.
# define ENDLESS 1						// SDL loop.

//Control global definitions.
# define ESC SDLK_ESCAPE				// SDL Keysym definition for ESC.

//Terminal output color codes.
# define T_NUL "\033[0m"				// Default terminal type color.
# define T_ORANGE "\033[1;33m"			// Bold orange terminal type color.
# define T_ORANGES "\033[0;33m"			// A slim orange terminal type color.
# define T_RED "\033[0;31m"				// A red terminal type color.
# define T_LGRAY "\033[0;37m"				// A light gray terminal type color.

//System-wise variables for run and check-up calls through the two programs.
typedef struct s_system {
	int		user_request;
}	t_system;

//Editor-wise variables used mainly for resolving the level editor program.
typedef struct s_editor {
	char		*file;
	char		buffer[MAX_READ + 1];
	char		array[MAX_READ + 1][MAX_READ + 1];
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
	int				x;
	int				y;
	uint32_t		color;
	int				scaler;
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

void	keyboard(t_graph *graph);

void	pixel_put(t_graph *graph);
void	sdl_loop(t_graph *graph);
void	*ft_memalloc(size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlen(const char *s);
#endif
