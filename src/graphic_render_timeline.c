/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_timeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:34:59 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/14 15:04:35 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	menu_string(t_gfx *gfx, int s)
{
	if (gfx_write(TXT_X * s, gfx->height / 4 - 60, gfx, "D R O W N I N G"))
		return (ERROR);
	if (gfx_write((TXT_X) * s, gfx->height / 3, gfx,
			"THE ATROCIOUS CAPTAIN OF THE FISHING BOAT 'WISH ME WELL'"))
		return (ERROR);
	if (gfx_write((TXT_X) * s, gfx->height / 3 + 40, gfx,
			"HAS THROWN YOU OVERBOARD! YOU ONLY HAVE MERE SECONDS TO"))
		return (ERROR);
	if (gfx_write((TXT_X) * s, gfx->height / 3 + 80, gfx,
			"ASURFACE BEFORE THE WATERY GRAVE CLAIMS YOUR LIFE!"))
		return (ERROR);
	if (gfx_write((TXT_X) * s, gfx->height / 3 + 220, gfx,
			"CLIMB THE CHAIN! SEEK OXYGEN BOTTLES FOR A QUICK RELIEF!"))
		return (ERROR);
	if (gfx_write(TXT_X * s, TXT_Y * s, gfx,
			"PRESS 'Z' TO PLAY .. 'X' HARD MODE .. 'C' EDITOR"))
		return (ERROR);
	return (0);
}

static int	event_string(t_drown *d, int s)
{
	if (d->map.map[(int)roundf(d->player.y / 64)]
		[(int)roundf(d->player.x / 64)][3] == '$')
		if (gfx_write((d->gfx.width / 3), (d->gfx.height / 2), &d->gfx,
				"PRESS 'E' TO COLLECT") == ERROR)
			return (ERROR);
	(void) s;
	return (0);
}

static int	ending_string(t_drown *d, int s)
{
	clear_surface(d);
	if (gfx_write(TXT_X * s, TXT_Y * s, &d->gfx,
			"CONGRATULATIONS! YOU ESCAPED!") == ERROR)
		return (ERROR);
	else
		return (0);
}

int	string_timeline(t_drown *d, int s)
{
	if (d->system.time > 600 && d->system.time < 3600)
		if (gfx_write(TXT_X * s, TXT_Y * s, &d->gfx,
				"...!!? N-NO! NO! NO NO NO NO!") == ERROR)
			return (ERROR);
	if (d->system.time > 4000 && d->system.time < 9200)
		if (gfx_write(TXT_X * s, TXT_Y * s, &d->gfx,
				"THIS CAN'T BE HAPPENING! I'M GONNA DROWN!") == ERROR)
			return (ERROR);
	if (d->system.time > 12000 && d->system.time < 22200)
		if (gfx_write(TXT_X * s, TXT_Y * s, &d->gfx,
				"AH!! THE CHAIN! THE BOAT WINCH!!") == ERROR)
			return (ERROR);
	if (d->system.time > 23200 && d->system.time < 32800)
		if (gfx_write(TXT_X * s, TXT_Y * s, &d->gfx,
				"IT'S DANGLING ABOVE! I NEED TO CATCH THE CHAIN!") == ERROR)
			return (ERROR);
	if (d->gfx.frame.bubble >= 13)
		if (gfx_write(TXT_X * s, TXT_Y * s, &d->gfx, "GAME OVER.") == ERROR)
			return (ERROR);
	if (event_string(d, s) == ERROR)
		return (ERROR);
	if (d->system.ending_state == REGULAR_ENDING)
		if (ending_string(d, s) == ERROR)
			return (ERROR);
	return (0);
}
