/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:56:40 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/08 21:00:06 by aviholai         ###   ########.fr       */
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

int	editor_sequence(t_graph *graph, t_system *system, t_editor *editor, t_index *index)
{
	print_array(editor, index);
	if (render(graph, editor, index) == ERROR)
		return (ERROR);
	if (system->user_request)
	{
		//
	}
	return (0);
}
