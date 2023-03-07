/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_timeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:34:59 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/07 20:10:35 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	string_timeline(t_drown *d)
{
	if (d->system.time > 600 && d->system.time < 3600)
		if (editor_test_write(&d->gfx, "...!!? N-NO! NO! NO NO NO NO!", d->gfx.width / 6, ((d->gfx.height / 4) * 3)) == ERROR)
			return (ERROR);
	if (d->system.time > 4000 && d->system.time < 9200)
		if (editor_test_write(&d->gfx, "THIS CAN'T BE HAPPENING! I'M GONNA DROWN!", d->gfx.width / 6, ((d->gfx.height / 4) * 3)) == ERROR)
			return (ERROR);
	if (d->system.time > 12000 && d->system.time < 22200)
		if (editor_test_write(&d->gfx, "AH!! THE ROPE! THE BOAT WINCH!!", d->gfx.width / 6, ((d->gfx.height / 4) * 3)) == ERROR)
			return (ERROR);
	if (d->system.time > 23200 && d->system.time < 32800)
		if (editor_test_write(&d->gfx, "IT'S DANGLING ABOVE! I NEED TO CATCH THE ROPE!", d->gfx.width / 6, ((d->gfx.height / 4) * 3)) == ERROR)
			return (ERROR);
	if (d->gfx.frame.bubble >= 13)
		if (editor_test_write(&d->gfx, "GAME OVER.", d->gfx.width / 6, ((d->gfx.height / 4) * 3)) == ERROR)
			return (ERROR);
	if (d->system.ending_state == REGULAR_ENDING)
	{
		SDL_FillRect(d->gfx.screen, NULL, 0);
		if (gfx_write(&d->gfx, "CONGRATULATIONS! YOU ESCAPED!") == ERROR)
			return (ERROR);
	}
	return (0);
}
