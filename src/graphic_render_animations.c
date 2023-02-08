/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_render_animations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:28:04 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/08 10:39:20 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	right_arm_loop(t_drown *d)
{
	if (d->system.time % 600 > 0 && d->system.time % 600 < 600)
		d->gfx.frame.right_arm = 1;
	if (d->system.time % 1200 > 0 && d->system.time % 1200 < 600)
		d->gfx.frame.right_arm = 2;
	if (d->system.time % 1800 > 0 && d->system.time % 1800 < 600)
		d->gfx.frame.right_arm = 1;
	if (d->system.time % 2400 > 0 && d->system.time % 2400 < 600)
		d->gfx.frame.right_arm = 0;
}

int			animation_loop(t_drown *d)
{
	right_arm_loop(d);
	return (0);
}
