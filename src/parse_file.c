/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:26 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 16:35:51 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	List all the allowed ASCII characters in a level file.
static int	validate_symbol(t_editor *editor, t_index *i)
{
	if (!(editor->buffer[i->i] == '#' || editor->buffer[i->i] == ' '
			|| editor->buffer[i->i] == 'S' || editor->buffer[i->i] == '\n'))
	{
		write(1, "\n" T_RED "Error: ", 15);
		write(1, &editor->buffer[i->i], 1);
		return (ERROR);
	}
	return (0);
}

static int	map_array_validation(t_editor *editor, t_index *i)
{
	int	e;

	if (i->y != (MAP_WIDTH / 2))
		return (error(BAD_WIDTH));
	e = 0;
	while (e < 25)
	{
		if (editor->map[0][e][0] != '#' || editor->map[e][0][0] != '#'
			|| editor->map[e][24][0] != '#' || editor->map[24][e][0] != '#')
			return (error(BAD_WALL));
		e++;
	}
	return (0);
}

//	Level file parsing function.
static int	validate_file(t_editor *editor, t_index *i)
{
	int	map_validate;

	while (editor->buffer[i->i])
	{
		if (validate_symbol(editor, i) == ERROR)
			return (error(BAD_SYMBOL));
		map_validate = buffer_to_map(editor->buffer, editor, i, MAP_WIDTH);
		if (map_validate == ERROR)
			return (ERROR);
		else if (map_validate == NEW_LINE)
		{
			i->y++;
			i->x = 0;
			i->i += (MAP_WIDTH + 2);
		}
		else
		{
			i->x++;
			i->i += 2;
		}
	}
	if (map_array_validation(editor, i) == ERROR)
		return (ERROR);
	return (0);
}

//	CheckS the validity of the level's filename. Filename must end in '.dn'.
static int	filename_check(t_editor *editor)
{
	int	i;

	i = 0;
	while (editor->file[i++])
	{
		if (editor->file[i] == '.' && editor->file[i + 1] == 'd'
			&& editor->file[i + 2] == 'n' && !(editor->file[i + 3]))
			break ;
		if (!(editor->file[i]))
			return (ERROR);
	}
	return (0);
}

//	Commits the level file through error management checks and ultimately
//	passes it on to the editor function.
int	read_file(t_drown *drown)
{
	int		fd;
	ssize_t	ret;

	if (!(drown->editor.file))
		return (error(NO_FILE));
	if (filename_check(&drown->editor) == ERROR)
		return (error(BAD_FILENAME));
	fd = open(drown->editor.file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, drown->editor.buffer, BUFFER_MAX);
	if (ret < 0)
		return (error(READ_FAIL));
	if (ret > BUFFER_MAX)
		return (error(FILE_MAX));
	drown->editor.buffer[ret] = '\0';
	if (validate_file(&drown->editor, &drown->index) == ERROR)
		return (ERROR);
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	if (graphic_interface(drown) == ERROR)
		return (ERROR);
	return (0);
}
