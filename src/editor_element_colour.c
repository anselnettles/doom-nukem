/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_element_colour.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:27:29 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 18:35:46 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	'X' = player_start
	'Z' = goal
	'@' = monster1
	'N' = monster2
	'$' = item1
	'J' = item2
	'K' = item3

	Non-established parameter selections are coloured as grey (0x008A8D8F).
*/
static uint32_t	colour_entity(t_map *map, int row_now, int col_now)
{
	uint32_t	colour;

	if (map->map[row_now][col_now][3] == 'X')
		colour = 0x00FFFFFF;
	else if (map->map[row_now][col_now][3] == 'Z')
		colour = 0x0000FF00;
	else if (map->map[row_now][col_now][3] == '@')
		colour = 0x00FF0000;
	else if (map->map[row_now][col_now][3] == 'N')
		colour = 0x008A8D8F;
	else if (map->map[row_now][col_now][3] == '$')
		colour = 0x000000FF;
	else if (map->map[row_now][col_now][3] == 'J')
		colour = 0x008A8D8F;
	else if (map->map[row_now][col_now][3] == 'K')
		colour = 0x008A8D8F;
	return (colour);
}

/*
	# = full wall
	0 = minimum wall height
	9 = maximum non-full wall height
*/
static uint32_t	colour_wall(t_map *map, int row_now, int col_now)
{
	uint32_t	colour;

	if (map->map[row_now][col_now][0] == '#')
		colour = 0x00FFCC00;
	else if (map->map[row_now][col_now][0] == '0')
		colour = 0x00222200;
	else if (map->map[row_now][col_now][0] == '1')
		colour = 0x00444400;
	else if (map->map[row_now][col_now][0] == '2')
		colour = 0x00665500;
	else if (map->map[row_now][col_now][0] == '3')
		colour = 0x00887700;
	else if (map->map[row_now][col_now][0] == '4')
		colour = 0x00998800;
	else if (map->map[row_now][col_now][0] == '5')
		colour = 0x00AA9900;
	else if (map->map[row_now][col_now][0] == '6')
		colour = 0x00BBAA00;
	else if (map->map[row_now][col_now][0] == '7')
		colour = 0x00CCBB00;
	else if (map->map[row_now][col_now][0] == '8')
		colour = 0x00DDCC00;
	else if (map->map[row_now][col_now][0] == '9')
		colour = 0x00FFDD00;
	return (colour);
}

/*
    Does not contain a condition for textures (param_index 1).
    Does not contain a condition for 45 degree (param_index 2).
	Does not contain a condition for special (param_index 4).

	1st condition: walls = no
	2nd condition: walls = no, entity = no
	3rd condition: walls = no, entity = no, secret = yes
*/
static uint32_t	img1_colouring(t_map *map, int row_now, int col_now)
{
	uint32_t	colour;

	if (map->map[row_now][col_now][3] != '.')
		colour = colour_entity(map, row_now, col_now);
	else
	{
		if (map->map[row_now][col_now][0] != '.')
			colour = colour_wall(map, row_now, col_now);
		else
			colour = 0x00000000;
	}
	return (colour);
}

uint32_t	element_colour(t_map *map, int row_now, int col_now,
	int image_switch)
{
	uint32_t	colour;

	if (image_switch == 1)
		colour = img1_colouring(map, row_now, col_now);
	else if (image_switch == 2)
		colour = colouring_img2_img3(map, row_now, col_now, 2);
	else if (image_switch == 3)
		colour = colouring_img2_img3(map, row_now, col_now, 3);
	return (colour);
}
