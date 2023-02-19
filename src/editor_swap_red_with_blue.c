/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_swap_red_with_blue.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: tturto                                   #+#    #+#             */
/*   Updated: 2023/02/19 14:45:19 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
 * Swaps hex colour code value Red with Blue. Function is used only due to
 * Piskel raw data export output being BGR instead of RGB.
 * XOR, OR, AND do not work in the same way as with binary format (10010101),
 * since values are 16-base
*/
uint32_t	swap_red_with_blue(uint32_t hex_value)
{
	uint32_t	only_r;
	uint32_t	only_g;
	uint32_t	only_b;

	if (hex_value == 0x00000000)
		return (hex_value);
	else
	{
		only_r = hex_value >> 16;
		only_g = hex_value >> 8;
		only_g = only_g << 24;
		only_g = only_g >> 16;
		only_b = hex_value << 24;
		only_b = only_b >> 8;
		hex_value = only_r + only_g + only_b;
		return (hex_value);
	}
}
