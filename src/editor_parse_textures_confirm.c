/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_parse_textures_confirm.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:59:27 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 12:59:35 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	confirm_memory_allocation_second_batch(t_gfx *gfx, int t, int f)
{
	(void)t;
	while (f < 4)
		if (gfx->texture[13].frame[f++].pixels == NULL)
			return (ERROR);
	f = 0;
	while (f < 3)
		if (gfx->texture[14].frame[f++].pixels == NULL)
			return (ERROR);
	f = 0;
	while (f < 3)
		if (gfx->texture[15].frame[f++].pixels == NULL)
			return (ERROR);
	f = 0;
	while (f < 3)
		if (gfx->texture[16].frame[f++].pixels == NULL)
			return (ERROR);
	return (0);
}

//	Texture 'A', 0:		Floor texture.	Frames: 0.			Size: 64 x 64
//	Texture 'B', 1:		Wall texture.	Frames: 0.			Size: 64 x 64
//	Texture 'C', 2:		Pillar.			Frames: 0.			Size: 64 x 64
//	Texture 'D', 3:		Crate texture.	Frames: 0.			Size: 64 x 64
//	Texture 'E', 4:		Sky texture.	Frames: 0.			Size: 720 x 240
//	Texture 'F', 5:		Right arm.		Frames: 0 to 4.		Size: 250 x 238
//	Texture 'G', 6:		Letters.		Frames: 0.			Size: 728 x 20
//	Texture 'H', 7:		Harpoon.		Frames: 0 to 6.		Size: 64 x 64
//	Texture 'I', 8:		Bottle.			Frames: 0 to 3.		Size: 38 x 64
//	Texture 'J', 9:		Timer.			Frames: 0 to 9.		Size: 60 x 90
//	Texture 'K', 10:	Bubble.			Frames: 0.			Size: 12 x 12
//	Texture 'L', 11:	Ammo.			Frames:	0 to 1.		Size: 32 x 45
//	Texture 'M', 12		Monster.		Placeholder.
//	Texture 'N', 13:	Algae texture.	Frames: 0 to 3.		Size: 64 x 64
//	Texture 'O', 14:	Rope chain.		Frames: 0 to 2.		Size: 16 x 64
//	Texture 'P', 15:	Transition.		Frames: 0 to 2.		Size: 642 x 48
//	Texture 'Q', 16:	Left arm.		Frames: 0 to 2.		Size: 182 x 492
int	confirm_memory_allocation_first_batch(t_gfx *gfx, int t, int f)
{
	while (t < 5)
		if (gfx->texture[t++].frame[f].pixels == NULL)
			return (ERROR);
	while (f < 5)
		if ((gfx->texture[5].frame[f++].pixels == NULL)
			|| (gfx->texture[6].frame[0].pixels == NULL))
			return (ERROR);
	f = 0;
	while (f < 7)
		if (gfx->texture[7].frame[f++].pixels == NULL)
			return (ERROR);
	f = 0;
	while (f < 4)
		if (gfx->texture[8].frame[f++].pixels == NULL)
			return (ERROR);
	f = 0;
	while (f < 10)
		if ((gfx->texture[9].frame[f++].pixels == NULL)
			|| (gfx->texture[10].frame[0].pixels == NULL)
			|| (gfx->texture[11].frame[0].pixels == NULL)
			|| (gfx->texture[11].frame[1].pixels == NULL))
			return (ERROR);
	return (0);
}
