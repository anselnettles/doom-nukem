/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:39:33 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/11 12:47:22 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

SDL_Surface	*img_load(char *path)
{
	SDL_Surface	*ret;
	SDL_Surface	*tmp;
	SDL_RWops	*rwops;

	if (!(rwops = SDL_RWFromFile(path, "r")))
		return (NULL);
	if (!(tmp = IMG_Load_RW(rwops, 1)))
		return (NULL);
	ret = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(tmp);
	return (ret);
}

int			initialize_textures(t_rain *rain)
{
	if (!(rain->texture.file[0] = img_load("textures/scifi.png")))
		return (ERROR);
	if (!(rain->texture.file[1] = img_load("textures/scifi2.png")))
		return (ERROR);
	if (!(rain->texture.file[2] = img_load("textures/scifi3.png")))
		return (ERROR);
	if (!(rain->texture.file[3] = img_load("textures/scifi4.png")))
		return (ERROR);
	return (0);
}
