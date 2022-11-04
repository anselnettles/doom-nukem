/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:26 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/04 21:14:23 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdio.h>

int	read_file(t_system *system, t_editor *editor)
{
	int	i;

	if (system->user_request)
		// to inform what the use is.
	if (!(editor->file))
		return(error(NO_FILE));
	i = 0;
	while (editor->file[i++])
	{
		if (editor->file[i] == '.' && editor->file[i + 1] == 'd'
				&& editor->file[i + 2] == 'n' && !(editor->file[i + 3]))
			break ;
		if (!(editor->file[i]))
			return (error(BAD_FILENAME));
	}
	return (0);
}
