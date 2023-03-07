/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_colouring_img2_img3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:47:46 by tturto            #+#    #+#             */
/*   Updated: 2023/03/07 16:55:29 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static uint32_t	colouring_img3(t_map *map, int row_now, int col_now)
{
	uint32_t	colour;

	colour = 0x0089ABE3;
	return (colour);
}

static uint32_t	colouring_img2(t_map *map, int row_now, int col_now)
{
	uint32_t	colour;

	colour = 0x0089ABE3;
	return (colour);
}

uint32_t	colouring_img2_img3(t_map *map, int row_now, int col_now,
	int image_switch)
{
	uint32_t	colour;

	if (image_switch == 2)
		colour = colouring_img2(map, row_now, col_now);
	else if (image_switch == 3)
		colour = colouring_img3(map, row_now, col_now);
	return (colour);
}
