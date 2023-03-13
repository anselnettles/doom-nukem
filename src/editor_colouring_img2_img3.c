/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_colouring_img2_img3.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:47:46 by tturto            #+#    #+#             */
/*   Updated: 2023/03/13 17:55:35 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

static uint32_t	colouring_img3(void)
{
	uint32_t	colour;

	colour = 0x0089ABE3;
	return (colour);
}

static uint32_t	colouring_img2(void)
{
	uint32_t	colour;

	colour = 0x0089ABE3;
	return (colour);
}

uint32_t	colouring_img2_img3(int image_switch)
{
	uint32_t	colour;

	if (image_switch == 2)
		colour = colouring_img2();
	else if (image_switch == 3)
		colour = colouring_img3();
	else
		colour = 0x00000000;
	return (colour);
}
