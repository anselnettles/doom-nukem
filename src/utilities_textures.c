/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:39:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/06 16:05:37 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

static int	second_texture_pull(t_rain *rain)
{
	t_texture *texture;
	(void) texture;
	(void) rain;
	return (0);
}

int			initialize_textures(t_rain *rain)
{
	t_texture *texture;

	texture = &rain->texture[0];
	//texture->img_ptr = //png to image
	//texture->img_addr = //png

	if (second_texture_pull(rain) == ERROR)
		return (ERROR);
	return (ERROR);
}
