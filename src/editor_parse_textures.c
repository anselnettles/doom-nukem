/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_parse_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 19:46:58 by aviholai          #+#    #+#             */
/*   Updated: 2023/03/13 12:39:35 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static void	hex_check_first(char *buf, t_index *i, char *str)
{
	i->hex_step = 0;
	while (buf[i->i] != ',' && buf[i->i] != '}'
		&& i->hex_step <= 9)
	{
		str[i->hex_step] = buf[i->i++];
		i->hex_step++;
	}
	str[i->hex_step] = '\0';
}

static void	hex_check_second(char *buf, t_index *i)
{
	if (buf[i->i++] == ',')
		i->hex_count++;
	if (buf[i->i] == ' ')
		i->i++;
	if (buf[i->i] == '\n')
		i->i++;
}

//	Applies the parsed HEX color value string to a suitable 'uint32_t' variable.
//	Due to the colors being in faulty blue-green-red format, they're reinstated
//	to suitable red-green-blue.
//	The hex values are saved one-by-one in the 'gfx->texture' arrays.
//	'Identity - 65' corresponds to the correct texture array, since in ASCII
//	table conversion to decimal numbers 65 is the difference of 'A' to 0.
static void	store_graphic(char identity, char *str, t_index *i, t_gfx *gfx)
{
	uint32_t	hex_value;

	hex_value = (uint32_t)strtol(str, NULL, 16);
	hex_value = swap_red_with_blue(hex_value);
	gfx->texture[identity - 65].frame[i->f].pixels[i->hex_count] = hex_value;
}

//	Parses through the map file's textures' HEX color values. Saves them in
//	variable 'str' and saves them in the 'gfx->texture' arrays one-by-one
//	via 'store_graphic()'.
static int	parse_textures(char identity, t_index *i, t_gfx *gfx, char *buf)
{
	char	str[11];

	while (buf[i->i++] != '\0')
	{
		if (buf[i->i] == identity)
		{
			while (buf[i->i - 1] != '{')
				i->i++;
			while (buf[i->i] != identity)
			{
				i->hex_count = 0;
				while (buf[i->i] != '}')
				{
					hex_check_first(buf, i, str);
					store_graphic(identity, str, i, gfx);
					if (buf[i->i] == '}' && i->i++ > -1)
						break ;
					hex_check_second(buf, i);
				}
				i->f++;
			}
			return (0);
		}
	}
	return (ERROR);
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
int	texture_allocation(char *buf, t_index *i, t_gfx *gfx)
{
	char	identity;

	if (memory_allocate_textures(gfx, 0) == ERROR)
		return (error(MALLOC_FAIL));
	identity = 'A';
	while (identity <= 'Q' )
	{
		i->i = 0;
		i->f = 0;
		if (parse_textures(identity, i, gfx, buf) == ERROR)
			return (error(PARSE_FAIL));
		identity++;
	}
	return (0);
}
