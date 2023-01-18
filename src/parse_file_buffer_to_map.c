/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_buffer_to_map.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:16:02 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/18 12:08:20 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

static char	check_for_start(char b[MAX + 1], t_index *i, t_editor *editor)
{
	if (b[i->i] == 'S' || b[i->i + 1] == 'S'
			|| b[i->i + MAP_WIDTH + 1] == 'S' || b[i->i + MAP_WIDTH + 2] == 'S')
	{
		editor->start_y = i->y;
		editor->start_x = i->x;
		return ('S');
	}
	else
		return (' ');
}

static char	check_for_walls(char b[MAX + 1], t_index *i)
{
	if (b[i->i] == '#' || b[i->i + 1] == '#'
			|| b[i->i + MAP_WIDTH + 1] == '#' || b[i->i + MAP_WIDTH + 2] == '#'
			|| b[i->i] == '/' || b[i->i + 1] == '/'
			|| b[i->i + MAP_WIDTH + 1] == '/' || b[i->i + MAP_WIDTH + 2] == '/'
			|| b[i->i] == '\\' || b[i->i + 1] == '\\'
			|| b[i->i + MAP_WIDTH + 1] == '\\' || b[i->i + MAP_WIDTH + 2] == '\\'
			|| b[i->i] == '*' || b[i->i + 1] == '*'
			|| b[i->i + MAP_WIDTH + 1] == '*' || b[i->i + MAP_WIDTH + 2] == '*'
			|| b[i->i] == '[' || b[i->i + 1] == '['
			|| b[i->i + MAP_WIDTH + 1] == '[' || b[i->i + MAP_WIDTH + 2] == '['
			|| b[i->i] == ']' || b[i->i + 1] == ']'
			|| b[i->i + MAP_WIDTH + 1] == ']' || b[i->i + MAP_WIDTH + 2] == ']')
		return ('#');
	else
		return (' ');
}

int	buffer_to_map(char b[MAX + 1], t_editor *editor, t_index *i)
{
	if ((i->i > 0) && ((i->i == MAP_WIDTH) || (i->i % (MAP_WIDTH + 1) == MAP_WIDTH)))
	{
		if (b[i->i] != '\n')
			return (error(BAD_WIDTH));
		editor->map[i->y][i->x][i->p] = '\0';
		return (NEW_LINE);
	}
	else
	{
		editor->map[i->y][i->x][0] = check_for_walls(b, i);
		editor->map[i->y][i->x][1] = check_for_start(b, i, editor);
		if (editor->map[i->y][i->x][0] == '#' && editor->map[i->y][i->x][1] == 'S')
			return (error(BAD_WALL));
	}
	return (0);
} 
