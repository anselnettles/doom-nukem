/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:26 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/07 12:14:27 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	validate_file(t_editor *editor)
{
	int	i;

	i = 0;
	while (editor->buffer[i++])
	{
		write (1, &editor->buffer[i], 1);
	}
	return (0);
}

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
		return (ERROR);
	if (system->user_request)
		//open editor?
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	return (0);
}
