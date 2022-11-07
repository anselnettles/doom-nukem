/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   level_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:56:40 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/07 20:46:24 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdio.h>

int	editor_sequence(t_system *system, t_editor *editor, t_index *index)
{
	//index->i = 0;
	index->j = 0;
	printf("rows is %d. width is %d. ", index->rows, index->width);
	while (index->j != index->rows)
	{
		write(1, editor->array[index->j], (size_t)index->width);
		write(1, "\n", 1);
#if 0
		while (index->i != '\0')
		{
			write (1, &editor->array[index->j][index->i], 1);
			index->i++;
		}
#endif
		index->j++;
	}
	if (system->user_request)
	{
		//
	}
	return (0);
}
