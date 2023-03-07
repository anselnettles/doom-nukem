/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_parse_textures_malloc_batches.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:53:49 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/07 20:47:13 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    Texture 'A', 0:		Floor texture.	Frames: 0.			Size: 64 x 64
    Texture 'B', 1:		Wall texture.	Frames: 0.			Size: 64 x 64
    Texture 'C', 2:		Pillar.			Frames: 0.			Size: 64 x 64
    Texture 'D', 3:		Crate texture.	Frames: 0.			Size: 64 x 64
    Texture 'E', 4:		Sky texture.	Frames: 0.			Size: 720 x 240
    Texture 'F', 5:		Right arm.		Frames: 0 to 4.		Size: 250 x 238
    Texture 'G', 6:		Letters.		Frames: 0.			Size: 728 x 20
    Texture 'H', 7:		Harpoon.		Frames: 0 to 6.		Size: 64 x 64
    Texture 'I', 8:		Bottle.			Frames: 0 to 3.		Size: 38 x 64
    Texture 'J', 9:		Timer.			Frames: 0 to 9.		Size: 60 x 90
    Texture 'K', 10:	Bubble.			Frames: 0.			Size: 12 x 12
    Texture 'L', 11:	Ammo.			Frames:	0 to 1.		Size: 32 x 45
    Texture 'M', 12		Monster.		Placeholder.
    Texture 'N', 13		Algae texture.	Frames: 0 to 3.		Size: 64 x 64
*/
static void	memory_allocate_textures_fourth_batch(t_gfx *gfx)
{
	gfx->texture[11].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (32 * 45));
	gfx->texture[11].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (32 * 45));
	gfx->texture[12].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (100 * 100));
	gfx->texture[13].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[13].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[13].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[13].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[14].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (16 * 64));
	gfx->texture[14].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (16 * 64));
	gfx->texture[14].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (16 * 64));
	gfx->texture[15].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (642 * 48));
	gfx->texture[15].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (642 * 48));
	gfx->texture[15].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (642 * 48));
}

static void	memory_allocate_textures_third_batch(t_gfx *gfx)
{
	gfx->texture[9].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[4].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[5].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[6].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[7].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[8].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[9].frame[9].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[10].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (12 * 12));
	memory_allocate_textures_fourth_batch(gfx);
}

void	memory_allocate_textures_second_batch(t_gfx *gfx)
{
	gfx->texture[7].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[7].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[7].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[7].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[7].frame[4].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[7].frame[5].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[7].frame[6].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[8].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	gfx->texture[8].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	gfx->texture[8].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	gfx->texture[8].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	memory_allocate_textures_third_batch(gfx);
}
