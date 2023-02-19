/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:36:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/17 18:36:51 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	deal_mouse(t_drown *data)
{
	data->player.dir += data->event.motion.xrel * DEGREES / 2;
	if (data->player.dir > 2 * PI)
		data->player.dir -= 2 * PI;
	if (data->player.dir < 0)
		data->player.dir += 2 * PI;
	data->player.dx = cosf(data->player.dir);
	data->player.dy = sinf(data->player.dir);
	data->gfx.centre -= data->event.motion.yrel * 8;
	if (data->gfx.centre > data->gfx.height)
		data->gfx.centre = data->gfx.height;
	if (data->gfx.centre < 0)
		data->gfx.centre = 0;
}
