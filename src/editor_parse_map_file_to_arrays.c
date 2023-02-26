/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_parse_map_file_to_arrays.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:46:58 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/26 22:03:33 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void store_graphic(char identity, char *str, t_index *i, t_gfx *gfx)
{
	uint32_t	hex_value;
	hex_value = (uint32_t)strtol(str, NULL, 16);
	hex_value = swap_red_with_blue(hex_value);
	gfx->texture[identity - 65].frame[i->f].pixels[i->hex_count] = hex_value;
	//printf("Frame %d. Index %d HEX: %d\n", i->f, i->hex_count, gfx->texture[identity - 65].frame[i->f].pixels[i->hex_count]);
}

static void parse_textures(char identity, t_index *i, t_gfx *gfx, char *buf)
{
	char	str[11];

	i.i = 0;
	while (buf[i.i] != identity)
		i.i++;
	i.i++;
	while (buf[i.i] != identity)
    {
        while (buf[i.i] != '{')
            i.i++;
        if (buf[i.i] == '{')
            i.i++;
        i.hex_count = 0;                 //reset "x"
        while (buf[i.i] != '}')          //loops per texture
        {
            i.hex_step = 0;
            while (buf[i.i] != ',' && buf[i.i] != '}')
            {
                str[i.hex_step] = buf[i.i];
                i.hex_step++;
                i.i++;
            }
            str[i.hex_step] = '\0';
            store_graphic(identity, str, i, gfx);
            if (buf[i.i] == '}')
            {
                i.i++;
                break ;
            }
            if (buf[i.i] == ',')
            {
                i.hex_count++;
                i.i++;
            }
            if (buf[i.i] == ' ')
                i.i++;
            if (buf[i.i] == '\n')
            {
                i.i++;
            }
        }
    }
}

//	Texture 'A', 0:	Floor texture.	Frames: 0.			Dimensions: 64 x 64.
//	Texture 'B', 1:	Wall texture.	Frames: 0.			Dimensions: 64 x 64.
//	Texture 'C', 2:	Pillar texture.	Frames: 0.			Dimensions: 64 x 64.
//	Texture 'D', 3:	Crate texture.	Frames: 0.			Dimensions: 64 x 64.
//	Texture 'E', 4:	Sky texture.	Frames: 0.			Dimensions: 128 x 64.
//	Texture 'F', 5:	Right arm.		Frames: 0 to 2.		Dimensions: 250 x 238.
//	Texture 'G', 6:	Letters.		Frames: 0.			Dimensions: 728 x 20.

int	memory_allocate_textures(t_index *i, t_gfx *gfx)
{
	if (!(gfx->texture[0].frame[0].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64) + 1)))
		return (ERROR);
	if (!(gfx->texture[1].frame[0].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64) + 1)))
		return (ERROR);
	if (!(gfx->texture[2].frame[0].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64) + 1)))
		return (ERROR);
	if (!(gfx->texture[3].frame[0].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (64 * 64) + 1)))
		return (ERROR);
	if (!(gfx->texture[4].frame[0].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (128 * 64) + 1)))
		return (ERROR);
	if (!(gfx->texture[5].frame[0].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (250 * 238) + 1)))
		return (ERROR);
	if (!(gfx->texture[5].frame[1].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (250 * 238) + 1)))
		return (ERROR);
	if (!(gfx->texture[5].frame[2].pixels = (uint32_t *)malloc(sizeof(uint32_t) * (250 * 238) + 1)))
		return (ERROR);
	return (0);
}

int	texture_allocation(char *buf, t_index *i, t_gfx *gfx)
{
	char	identity;

	if (memory_allocate_textures(i, gfx) == ERROR)
	{
		write(1, "Malloc error.\n", 14);
		return (ERROR);
	}
	identity = 'A';
	while (identity <= 'F' ) // To be continued all the way to final map file identity.
	{
		parse_textures(identity, i, gfx, buf);
		identity++;
	}
	printf("This is 'right_arm' frame 2, pixel 53249: %d\n", gfx->texture[5].frame[2].pixels[53249]);
    return (0);
}
