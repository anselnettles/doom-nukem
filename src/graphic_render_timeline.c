/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_timeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:34:59 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/10 12:38:31 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	string_timeline(t_drown *d)
{
	if (d->system.time < 3200)
	{
		if (gfx_write(&d->gfx, "HELLO WORLD.") == ERROR)
			return (ERROR);
	}
	if (d->system.time > 3200 && (d->system.time % 1000 > 0 && d->system.time % 1000 < 500))
	{
		if (gfx_write(&d->gfx, "\"A QUICK BROWN FOX'S JUMP OVERS THE LAZY DOG!??\"") == ERROR)
			return (ERROR);
	}
	return (0);
}
