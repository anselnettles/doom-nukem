/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_parse_textures_alloc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:28:57 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 12:55:50 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	memory_allocate_textures_fifth_batch(t_gfx *gfx)
{
	gfx->texture[TRANSITION].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (642 * 48));
	gfx->texture[TRANSITION].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (642 * 48));
	gfx->texture[TRANSITION].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (642 * 48));
	gfx->texture[LEFT_ARM].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (182 * 492));
	gfx->texture[LEFT_ARM].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (182 * 492));
	gfx->texture[LEFT_ARM].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (182 * 492));
}

static void	memory_allocate_textures_fourth_batch(t_gfx *gfx)
{
	gfx->texture[AMMO].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (32 * 45));
	gfx->texture[AMMO].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (32 * 45));
	gfx->texture[MONSTER].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (100 * 100));
	gfx->texture[ALGAE].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[ALGAE].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[ALGAE].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[ALGAE].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[CHAIN].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (16 * 64));
	gfx->texture[CHAIN].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (16 * 64));
	gfx->texture[CHAIN].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (16 * 64));
	memory_allocate_textures_fifth_batch(gfx);
}

static void	memory_allocate_textures_third_batch(t_gfx *gfx)
{
	gfx->texture[TIMER].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[4].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[5].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[6].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[7].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[8].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[TIMER].frame[9].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (60 * 90));
	gfx->texture[BUBBLE].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (12 * 12));
	memory_allocate_textures_fourth_batch(gfx);
}

static void	memory_allocate_textures_second_batch(t_gfx *gfx)
{
	gfx->texture[HARPOON].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[HARPOON].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[HARPOON].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[HARPOON].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[HARPOON].frame[4].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[HARPOON].frame[5].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[HARPOON].frame[6].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[BOTTLE].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	gfx->texture[BOTTLE].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	gfx->texture[BOTTLE].frame[2].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	gfx->texture[BOTTLE].frame[3].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (38 * 64));
	memory_allocate_textures_third_batch(gfx);
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
int	memory_allocate_textures(t_gfx *gfx, int f)
{
	gfx->texture[FLOOR].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[WALL].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[PILLAR].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[CRATE].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[SKYBOX].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (720 * 480));
	while (f < 5)
		gfx->texture[RIGHT_ARM].frame[f++].pixels
			= (uint32_t *)malloc(sizeof(uint32_t) * (250 * 238));
	gfx->texture[LETTERS].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (728 * 20));
	memory_allocate_textures_second_batch(gfx);
	if (confirm_memory_allocation_first_batch(gfx, 0, 0) == ERROR
		|| (confirm_memory_allocation_second_batch(gfx, 0, 0)) == ERROR)
		return (ERROR);
	return (0);
}
