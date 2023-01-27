/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 12:24:14 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/26 16:26:13 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Surface	*img_load(char *path)
{
	SDL_Surface	*ret;
	SDL_Surface	*tmp;
	SDL_RWops	*rwops;

	rwops = SDL_RWFromFile(path, "r");
	tmp = IMG_Load_RW(rwops, 1);
	if (tmp == NULL || rwops == NULL)
		return (NULL);
	ret = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(tmp);
	return (ret);
}

void	clear_screen(t_main *data)
{
	SDL_Surface	*screen;

	if (!(screen = SDL_GetWindowSurface(data->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
	SDL_FreeSurface(screen);
}

void	draw_map(t_main *data)		//DRAWS 2D MAP
{
	int			x;
	int			y;
	SDL_Surface	*screen;

	x = 0;
	y = 0;
	data->rect.x = 0;
	data->rect.y = 0;
	data->rect.h = MMHEIGHT / (data->map.y_max / BITS);
	data->rect.w = MMWIDTH / (data->map.x_max / BITS);
	if (!(screen = SDL_GetWindowSurface(data->window)))
		printf("screen couldnt be created! SDL_Error: %s\n", SDL_GetError());
	while (y < data->map.y_max)
	{
		data->rect.x = 0;
		x = 0;
		while (x < data->map.x_max)
		{
			if (data->map.map[y][x] != ' ')
			{
				SDL_FillRect(screen, &data->rect,
					SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
			}
			else
				SDL_FillRect(screen, &data->rect,
					SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
			data->rect.x += MMWIDTH / (data->map.x_max / BITS);
			x += BITS;
		}
		y += BITS;
		data->rect.y += MMHEIGHT / (data->map.y_max / BITS);
	}
	data->rect.x = MMWIDTH / (data->map.x_max / BITS) * (data->player.x / BITS);
	data->rect.y = MMHEIGHT / (data->map.y_max / BITS) * (data->player.y / BITS);
	data->rect.h = 5;
	data->rect.w = 5;
	SDL_FillRect(screen, &data->rect, SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00));
	SDL_FreeSurface(screen);
}