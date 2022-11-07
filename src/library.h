/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:26:57 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/07 10:32:33 by aviholai         ###   ########.fr       */
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

//System-wise global definitions
# define RUN_GAME 1						// User request for running the game.
# define RUN_LEVEL_EDITOR 2				// User request for running the editor.
# define ERROR 1						// Reference to return value.
# define MAX_READ 5000					// Irrelevant level size maximum.

//Terminal output color codes.
# define T_NUL "\033[0m"				// Default terminal type color.
# define T_ORANGE "\033[1;33m"			// Bold orange terminal type color.
# define T_RED "\033[0;31m"				// A red terminal type color.

//System-wise variables for run and check-up calls through the two programs.
typedef struct s_system {
	int		user_request;
}	t_system;

//Editor-wise variables used mainly for resolving the level editor program.
typedef struct s_editor {
	char		*file;
	char		buffer[MAX_READ + 1];
}	t_editor;

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
}	t_error;

int		error(int code);				// Error management function.
int		main(int argc, char **argv);	// The main function.
int		read_file(t_system *system, t_editor *editor);	// Level file reader.

size_t	ft_strlen(const char *s);		// Measure the length of applied string.

#endif
