/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utilities_read.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 17:25:51 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 17:31:02 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	These functions are only called by read_map().
*/
void	open_check(int *fd, char *map_file)
{
	*fd = open(map_file, O_RDONLY);
	if (*fd < 0)
	{
		tt_errors("read_map: open() fail.");
		exit(-1);
	}
}

void	read_check(int fd, int *ret, char *buf, int size)
{
	*ret = read(fd, buf, size);
	if (*ret <= 0)
	{
		tt_errors("read_map: read() fail.");
		exit(-1);
	}
}
