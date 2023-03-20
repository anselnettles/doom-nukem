/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:30:05 by tturto            #+#    #+#             */
/*   Updated: 2023/03/14 18:24:23 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static int	is_ascii(char *buf)
{
	if (*buf < ASCII_MIN && *buf > ASCII_MAX)
	{
		tt_errors("Buffer characters must be ASCII.");
		return (0);
	}
	return (1);
}

static void	space_and_nl_check(char *buf,
	unsigned short int *index_buf_col, unsigned short int *index_buf_row,
	t_editor_images *images)
{
	if (*buf == ' ' || (*index_buf_col == images->buffer_columns - 1))
		(*index_buf_col)++;
	else if (*buf == '\n')
		(*index_buf_row)++;
}

static int	is_param_valid(char *buf, unsigned short int *set_count)
{
	if (*buf >= ASCII_MIN && *buf <= ASCII_MAX && *buf != ' '
		&& *buf != '\n' && *buf != 'A')
		(*set_count)++;
	else
	{
		tt_errors("Invalid buffer: Format of one set.");
		return (0);
	}
	return (1);
}

int	validate(char *buf, t_editor_images *images,
	unsigned short int index_buf_col, unsigned short int index_buf_row)
{
	unsigned short int	set_count;

	while (index_buf_row < images->buffer_rows)
	{
		index_buf_col = 0;
		while (index_buf_col < images->buffer_columns)
		{
			set_count = 0;
			while (set_count < PARAM_COUNT)
			{
				if (is_param_valid(buf, &set_count) != 1)
					return (0);
				buf++;
			}
			space_and_nl_check(buf, &index_buf_col, &index_buf_row, images);
			if (*buf == 'A')
				break ;
			if (is_ascii(buf) != 1)
				return (0);
			buf++;
		}
		if (*buf == 'A')
			break ;
	}
	return (1);
}
