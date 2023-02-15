/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_timeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:34:59 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/10 19:06:26 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	string_timeline(t_drown *d)
{
	if (d->system.time > 600 && d->system.time < 3600)
		if (gfx_write(&d->gfx, "...!!? N-NO! NO! NO NO NO NO!") == ERROR)
			return (ERROR);
	if (d->system.time > 4000 && d->system.time < 9200)
		if (gfx_write(&d->gfx,
				"THIS CAN'T BE HAPPENING! I'M GONNA DROWN!") == ERROR)
			return (ERROR);
	if (d->system.time > 12000 && d->system.time < 22200)
		if (gfx_write(&d->gfx, "AH!! THE ROPE! THE BOAT WINCH!!") == ERROR)
			return (ERROR);
	if (d->system.time > 23200 && d->system.time < 32800)
		if (gfx_write(&d->gfx,
					"IT'S DANGLING ABOVE! I NEED TO CATCH THE ROPE!") == ERROR)
			return (ERROR);
	return (0);
}