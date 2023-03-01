/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_parse_textures_malloc.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 09:28:57 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/01 17:50:54 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Texture 'A', 0:		Floor texture.	Frames: 0.			Size: 64 x 64
//	Texture 'B', 1:		Wall texture.	Frames: 0.			Size: 64 x 64
//	Texture 'C', 2:		Pillar.			Frames: 0.			Size: 64 x 64
//	Texture 'D', 3:		Crate texture.	Frames: 0.			Size: 64 x 64
//	Texture 'E', 4:		Sky texture.	Frames: 0.			Size: 963 x 240
//	Texture 'F', 5:		Right arm.		Frames: 0 to 4.		Size: 250 x 238
//	Texture 'G', 6:		Letters.		Frames: 0.			Size: 728 x 20
//	Texture 'H', 7:		Harpoon.		Frames: 0 to 6.		Size: 64 x 64
//	Texture 'I', 8:		Bottle.			Frames: 0 to 3.		Size: 38 x 64
//	Texture 'J', 9:		Timer.			Frames: 0 to 9.		Size: 60 x 90
//	Texture 'K', 10:	Bubble.			Frames: 0.			Size: 12 x 12
//	Texture 'L', 11:	Ammo.			Frames:	0 to 1.		Size: 32 x 45

static void	memory_allocate_textures_fourth_batch(t_gfx *gfx)
{
	gfx->texture[11].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (32 * 45));
	gfx->texture[11].frame[1].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (32 * 45));
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

static void	memory_allocate_textures_second_batch(t_gfx *gfx)
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

static int	confirm_memory_allocation_second_batch(t_gfx *gfx, int t, int f)
{
	(void)f;
	(void)t;
	(void)gfx;
	return (0);
}

static int	confirm_memory_allocation_first_batch(t_gfx *gfx, int t, int f)
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

int	memory_allocate_textures(t_gfx *gfx, int f)
{
	gfx->texture[0].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[1].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[2].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[3].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64));
	gfx->texture[4].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (720 * 240));
	while (f < 5)
		gfx->texture[5].frame[f++].pixels
			= (uint32_t *)malloc(sizeof(uint32_t) * (250 * 238));
	gfx->texture[6].frame[0].pixels
		= (uint32_t *)malloc(sizeof(uint32_t) * (728 * 20));
	memory_allocate_textures_second_batch(gfx);
	if (confirm_memory_allocation_first_batch(gfx, 0, 0) == ERROR
		|| (confirm_memory_allocation_second_batch(gfx, 0, 0)) == ERROR)
		return (ERROR);
	return (0);
}
