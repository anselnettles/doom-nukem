/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:26 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/07 18:50:16 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

// Comments are allowed in level files within braces.

static int	check_comments(t_editor *editor, int i)
{
	if (editor->buffer[i] == '{')
	{
		while (editor->buffer[i] && editor->buffer[i] != '}')
			i++;
		if (editor->buffer[i])
			i++;
	}
	return (i);
}

//	List all the allowed ASCII characters in a level file.

static int	validate_symbol(t_editor *editor, int i)
{
	if (!(editor->buffer[i] == 0 || editor->buffer[i] == '\n'
			|| editor->buffer[i] == ' ' || editor->buffer[i] == '#'
			|| editor->buffer[i] == '*' || editor->buffer[i] == '\\'
			|| (editor->buffer[i] >= '/' && editor->buffer[i] <= '9')
			|| (editor->buffer[i] >= 'A' && editor->buffer[i] <= 'Z')
			|| (editor->buffer[i] >= 'a' && editor->buffer[i] <= 'j')))
	{
		write(1, "\n" T_RED "Error: ", 15);
		write(1, &editor->buffer[i], 1);
		return (ERROR);
	}
	return (0);
}

//	Level file parsing function.

int	validate_file(t_editor *editor)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (editor->buffer[i])
	{
		i = check_comments(editor, i);
		write(1, &editor->buffer[i], 1);
		if (validate_symbol(editor, i) == ERROR)
			return (ERROR);
		if (editor->buffer[i] == '\n')
		{
			editor->array[k][j] = '\0';
			j = 0;
			k++;
		}
		else
			editor->array[k][j] = editor->buffer[i];
			j++;
		i++;
	}
	return (0);
}

// Checks the validity of the level's filename. Filename must end in '.dn'.

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

// Commits the level file through error management checks and ultimately
// passes it on to the editor function.

int	read_file(t_system *system, t_editor *editor)
{
	int		fd;
	ssize_t	ret;

	if (!(editor->file))
		return (error(NO_FILE));
	if (filename_check(editor) == ERROR)
		return (error(BAD_FILENAME));
	fd = open(editor->file, O_RDONLY);
	if (fd == -1)
		return (error(OPEN_FAIL));
	ret = read(fd, editor->buffer, MAX_READ);
	if (ret < 0)
		return (error(READ_FAIL));
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	editor->buffer[ret] = '\0';
	if (validate_file(editor) == ERROR)
		return (error(BAD_SYMBOL));
	if (system->user_request)
		//open editor?
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	return (0);
}
