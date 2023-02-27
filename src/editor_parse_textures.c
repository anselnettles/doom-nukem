/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_parse_map_file_to_arrays.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:46:58 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/27 09:32:52 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void store_graphic(char identity, char *str, t_index *i, t_gfx *gfx)
{
	uint32_t	hex_value;
	hex_value = (uint32_t)strtol(str, NULL, 16);
	hex_value = swap_red_with_blue(hex_value);
	gfx->texture[identity - 65].frame[i->f].pixels[i->hex_count] = hex_value;
	if (identity - 65 < 7)
		printf("ID: %d. Frame: %d. Index: %d HEX: %d\n", (identity - 65), i->f, i->hex_count, gfx->texture[identity - 65].frame[i->f].pixels[i->hex_count]);
}

static int	parse_textures(char identity, t_index *i, t_gfx *gfx, char *buf)
{
	char	str[11];

	i->i = 0;
	while (buf[i->i] != '\0')
	{
		if (buf[i->i] == identity)
		{
			while (buf[i->i - 1] != '{')
				i->i++;
        		i->hex_count = 0;                 //reset "x"
        		while (buf[i->i] != '}')          //loops per texture
        		{
            			i->hex_step = 0;
            			while (buf[i->i] != ',' && buf[i->i] != '}')
            			{
                			str[i->hex_step] = buf[i->i];
                			i->hex_step++;
                			i->i++;
            			}
            			str[i->hex_step] = '\0';
            			store_graphic(identity, str, i, gfx);
            			if (buf[i->i] == '}')
            			{
                			i->i++;
                			break ;
            			}
            			if (buf[i->i] == ',')
            			{
                			i->hex_count++;
                			i->i++;
            			}
            			if (buf[i->i] == ' ')
                			i->i++;
            			if (buf[i->i] == '\n')
            			{
                			i->i++;
            			}
        		}
			return (0);
		}
	i->i++;
	}
	return (ERROR);
}

//	Texture 'A', 0:		Floor texture.	Frames: 0.			Size: 64 x 64
//	Texture 'B', 1:		Wall texture.	Frames: 0.			Size: 64 x 64
//	Texture 'C', 2:		Pillar.			Frames: 0.			Size: 64 x 64
//	Texture 'D', 3:		Crate texture.	Frames: 0.			Size: 64 x 64
//	Texture 'E', 4:		Sky texture.	Frames: 0.			Size: 128 x 64
//	Texture 'F', 5:		Right arm.		Frames: 0 to 4.		Size: 250 x 238
//	Texture 'G', 6:		Letters.		Frames: 0.			Size: 728 x 20
//	Texture 'H', 7:		Harpoon.		Frames: 0 to 6.		Size: 64 x 64
//	Texture 'I', 8:		Bottle.			Frames: 0 to 3.		Size: 38 x 64
//	Texture 'J', 9:		Timer.			Frames: 0 to 9.		Size: 60 x 90
//	Texture 'K', 10:	Bubble.			Frames: 0.			Size: 12 x 12
//	Texture 'L', 11:	Ammo.			Frames:	0 to 2.		Size: 32 x 45

int	texture_allocation(char *buf, t_index *i, t_gfx *gfx)
{
	char	identity;

	memory_allocate_textures(gfx);
	identity = 'A';
	while (identity <= 'G' ) // To be continued all the way to final map file identity.
	{
		if (parse_textures(identity, i, gfx, buf) == ERROR)
			return (error(PARSE_FAIL));
		identity++;
	}
	printf("(This is 'right_arm' frame 2, pixel 53249): %d\n", gfx->texture[5].frame[2].pixels[53249]);
	return (0);
}
