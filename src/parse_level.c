/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:33:26 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/04 19:01:28 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#include <stdio.h>

int	read_file(t_system *system, t_editor *editor)
{
	if (system->user_request)
		printf("yeehaaw. ");
	if (editor->file)
		printf("hot dang. ");
	return (0);
}
