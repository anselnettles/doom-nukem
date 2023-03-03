/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_pix_put.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:32:46 by tturto            #+#    #+#             */
/*   Updated: 2023/02/28 18:19:02 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	scale is not used in map_editor.
	leave here for future usage.
*/
int	editor_pix_put(t_gfx *gfx, int x, int y, uint32_t colour)
{
	uint32_t	*pix;
	int			wth;
	int			scale;

	scale = 2;
	wth = gfx->width;
	pix = gfx->screen->pixels;
	pix[(x) + (y * wth)] = colour;
	if (scale >= 2)
	{
		pix[(x + 1) + (y * wth)] = colour;
		pix[(x) + ((y + 1) * wth)] = colour;
		pix[(x + 1) + ((y + 1) * wth)] = colour;
	}
	return (0);
}
