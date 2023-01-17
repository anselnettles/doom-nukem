/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:26 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/17 19:25:44 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

//	Comments are allowed in level files within braces.
static void	check_comments(t_editor *editor, t_index *i)
{
	write(1, &editor->buffer[i->i], 1);
	if (editor->buffer[i->i] == '{')
	{
		while (editor->buffer[i->i] && editor->buffer[i->i] != '}')
		{
			i->i++;
			i->x++;
			write(1, &editor->buffer[i->i], 1);
		}
		if (editor->buffer[i->i])
		{
			i->i++;
			i->x++;
		}
		write(1, &editor->buffer[i->i], 1);
	}
}

//	List all the allowed ASCII characters in a level file.
static int	validate_symbol(t_editor *editor, t_index *i)
{
	if (!(editor->buffer[i->i] == 0 || editor->buffer[i->i] == '\n'
			|| editor->buffer[i->i] == ' ' || editor->buffer[i->i] == '#'
			|| editor->buffer[i->i] == '*' || editor->buffer[i->i] == '\\'
			|| (editor->buffer[i->i] >= '/' && editor->buffer[i->i] <= '9')
			|| (editor->buffer[i->i] >= 'A' && editor->buffer[i->i] <= 'Z')
			|| (editor->buffer[i->i] >= 'a' && editor->buffer[i->i] <= 'j')
			|| (editor->buffer[i->i] == '[' || editor->buffer[i->i] == ']')))
	{
		write(1, "\n" T_RED "Error: ", 15);
		write(1, &editor->buffer[i->i], 1);
		return (ERROR);
	}
	return (0);
}

//	Level file parsing function.
static int	validate_file(t_editor *editor, t_index *i)
{
	int	map_validate;

	while (editor->buffer[i->i])
	{
		check_comments(editor, i);
		if (validate_symbol(editor, i) == ERROR)
			return (error(BAD_SYMBOL));
		map_validate = buffer_to_map(editor->buffer, editor, i);
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
int	read_file(t_rain *rain)
{
	int		fd;
	ssize_t	ret;

	if (!(rain->editor.file))
		return (error(NO_FILE));
	if (filename_check(&rain->editor) == ERROR)
		return (error(BAD_FILENAME));
	fd = open(rain->editor.file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, rain->editor.buffer, MAX);
	if (ret < 0)
		return (error(READ_FAIL));
	if (ret > MAX)
		return (error(FILE_MAX));
	rain->editor.buffer[ret] = '\0';
	if (validate_file(&rain->editor, &rain->index) == ERROR)
		return (ERROR);
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	if (editor_sequence(rain) == ERROR)
		return (error(EDITOR_FAIL));
	return (0);
}
