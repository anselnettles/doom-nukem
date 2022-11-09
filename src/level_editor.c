/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:56:40 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/09 13:06:46 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	print_array(t_editor *editor, t_index *index)
{
	index->i = 0;
	//write(1, T_RED, 10);
	while (index->i != index->y)
	{
		write(1, editor->array[index->i], (size_t)index->width);
		write(1, "\n", 1);
		index->i++;
	}
	//write(1, T_NUL, 7);
}

int	editor_sequence(t_rain *rain)
{
	print_array(&rain->editor, &rain->index);
	if (graphic_interface(rain) == ERROR)
		return (ERROR);
	return (0);
}
