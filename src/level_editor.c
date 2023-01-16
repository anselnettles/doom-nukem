/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:56:40 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/16 08:53:59 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitter_cold_droplets_in_autumn_rain.h"

void	print_array(t_editor *editor, t_index *index)
{
	index->i = 0;
	while (index->i != index->y)
	{
		write(1, editor->array[index->i], (size_t)index->width);
		write(1, "\n", 1);
		index->i++;
	}
}

int	array_to_stage(char a[MAX +1][MAX + 1], t_stage *stage, t_index *i)
{
	int	y;
	int	x;
	int	y2;
	int	x2;

	y = 1;
	x = 1;
	y2 = 0;
	x2 = 0;
	while (y <= i->y)
	{
		while (x <= i->width)
		{
			if (a[y][x] == '#' || a[y + 1][x] == '#' || a[y][x + 1] == '#'
			|| a[y + 1][x + 1] == '#' || a[y][x] == '/'
			|| a[y + 1][x] == '/' || a[y][x + 1] == '/'
			|| a[y + 1][x + 1] == '/' || a[y][x] == '\\'
			|| a[y + 1][x] == '\\' || a[y][x + 1] == '\\'
			|| a[y + 1][x + 1] == '\\' || a[y][x] == '*'
			|| a[y + 1][x] == '*' || a[y][x + 1] == '*'
			|| a[y + 1][x + 1] == '*' || a[y][x] == '['
			|| a[y + 1][x] == '[' || a[y][x + 1] == '['
			|| a[y + 1][x + 1] == '[' || a[y][x] == ']'
			|| a[y + 1][x] == ']' || a[y][x + 1] == ']'
			|| a[y + 1][x + 1] == ']')
				stage->grid[y2][x2] = '#';
			else if (a[y][x] == 'S' || a[y + 1][x] == 'S'
			|| a[y][x + 1] == 'S' || a[y + 1][x + 1] == 'S')
			{
				stage->grid[y2][x2] = 'S';
				stage->start_y = y2;
				stage->start_x = x2;
			}
			write(1, &stage->grid[y2][x2], 1);
			if (stage->grid[y2][x2] == '\0')
				write(1, " ", 1);
			x += 2;
			x2++;
		}
		y += 2;
		y2++;
		write(1, "\n", 1);
		x2 = 0;
		x = 1;
	}
	return (0);
}

int	editor_sequence(t_rain *r)
{
	print_array(&r->editor, &r->index);
	if (array_to_stage(r->editor.array, &r->stage, &r->index) == ERROR)
		return (ERROR);
	if (graphic_interface(r) == ERROR)
		return (ERROR);
	return (0);
}
