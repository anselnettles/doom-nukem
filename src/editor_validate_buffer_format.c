/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_validate_buffer_format.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 20:13:47 by tturto            #+#    #+#             */
/*   Updated: 2023/03/02 20:13:48 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	validate(char *buf, t_editor_images *images)
{
	unsigned short int	set_count;
	unsigned short int	index_buffer_column;
	unsigned short int	index_buf_row;

	set_count = 0;
	index_buf_row = 0;
	while (index_buf_row < images->buffer_rows)
	{
		index_buffer_column = 0;
		while(index_buffer_column < images->buffer_columns)
		{
			set_count = 0;
			while (set_count < PARAM_COUNT)
			{
				if (*buf >= ASCII_MIN && *buf <= ASCII_MAX && *buf != ' '
					&& *buf != '\n' && *buf != 'A')
					set_count++;
				else
				{
					tt_errors("Invalid buffer: Format of one set.");
					return (0);
				}
				buf++;
			}
			if (*buf == ' ' || (index_buffer_column == images->buffer_columns - 1))
				index_buffer_column++;
			else if (*buf == '\n')
				index_buf_row++;
			else if (*buf == 'A')
				break ;
			else if (*buf < ASCII_MIN && *buf > ASCII_MAX)
			{
				tt_errors("Buffer characters must be ASCII.");
				return (0);
			}
			buf++;
		}
		if (*buf == 'A')
			break ;
	}
	return (1);
}

/*
	Compares buffer row lengths. Row separator is '\n'.

	Return 1 on success, 0 on fail.
*/
static int	buffer_row_len_validation(char *buf)
{
	unsigned short int	row_len_current;
	unsigned short int	row_len_temp;
	unsigned short int	rswitch;

	row_len_current = 0;
	rswitch = 0;
	while (*buf != '\0')
	{
		row_len_temp = 0;
		while (*buf != '\n')
		{
			row_len_temp++;
			buf++;
		}
		if (rswitch == 1)
		{
			row_len_current = row_len_temp;
			if (row_len_current != row_len_temp)
			{
				tt_errors("Map file error: Map rows are of different length.");
				return (0);
			}
		}
		else if (rswitch == 0)
			row_len_current = row_len_temp;
		rswitch = 1;
		buf++;
	}
	return (1);
}

/*
	Validates if the first set is correct. Set means
	a string of characters, length of PARAM_COUNT.

	Return 1 on success, 0 on fail.
*/
static int buffer_1_set_validation(char *buf)
{
	unsigned short int	index;

	index = 0;
	while (index < PARAM_COUNT)
	{
		if (*buf >= ASCII_MIN && *buf <= ASCII_MAX && *buf != ' '
			&& *buf != '\n' && *buf != '\0')
			buf++;
		else
		{
			tt_errors("Even the first set is invalid.");
			return (0);
		}
		index++;
	}
	return (1);
}

/*
	Counts buffer row and column count.
	Validates buffer row length.
	Stores buffer row and column count.

	Return 1 on success, 0 on fail.
*/
static int count_buffer_data(char *buf, t_editor_images *images)
{
    int row_bytes;
	
	if (buffer_1_set_validation(buf) != 1)
		return (0);
	if (buffer_row_len_validation(buf) != 1)
		return (0);
    row_bytes = 0;
    while (*buf != '\n')
    {
        row_bytes++;
        buf++;
    }
	images->buffer_columns = (row_bytes + 1) / (PARAM_COUNT + 1);
	while(*buf != '\0')
	{
		if (*buf == '\n')
			images->buffer_rows++;
		buf++;
	}
	return (1);
}

/*
	Validates the buffer by checking if a set of 5 (PARAM_COUNT) characters is
	followed by ' ' and '\n'.
	
	Buffer is char *buf, read from a map file.
	Map file is to follow a pre-defined standard.

	Return 1 on success, 0 on fail.
*/

// !!! note, using same *buf in each function. Check if rolling is local or
// !!! global. If global, either use index [i] or try to localize.
int	validate_buffer_format(char *buf, t_editor_images *images)
{
	if (count_buffer_data(buf, images) != 1)
		return (0);
	if (validate(buf, images) != 1)
		return (0);
	return (1);
}
