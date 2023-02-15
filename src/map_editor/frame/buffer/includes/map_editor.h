#ifndef MAP_EDITOR_H
# define MAP_EDITOR_H
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# define PARAM_COUNT 5
# define ASCII_MIN 32
# define ASCII_MAX 127

typedef struct s_editor_images
{
	unsigned short int	buffer_rows;
	unsigned short int	buffer_columns;
}	t_editor_images;

int	validate_buffer_format(char *buf, t_editor_images *images);
void    tt_errors(char *error_msg);

#endif
