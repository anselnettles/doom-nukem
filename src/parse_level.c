/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:26 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/06 16:42:22 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

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
	ret = read(fd, editor->buffer, MAX_READ + 1);
	if (ret < 0)
		return (error(READ_FAIL));
	if (ret > MAX_READ)
		return (error(FILE_MAX));
	if (system->user_request)
	{
		//requested.
	}
	if (close(fd) == -1)
		return (error(CLOSE_FAIL));
	return (0);
}
