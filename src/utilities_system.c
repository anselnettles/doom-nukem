/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/02/07 17:22:50 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void	sdl_loop(t_drown *data)
{
	data->keyboard = SDL_GetKeyboardState(NULL);
	while (data->play_state == PLAY)
	{
		while(SDL_PollEvent(&data->event))
		{
			if (data->event.type == SDL_QUIT)
				data->play_state = EXIT;
			if (data->event.type == SDL_KEYDOWN || data->event.type == SDL_KEYUP)
				deal_key(data);
			if (data->event.type == SDL_MOUSEMOTION)
				deal_mouse(data);
		}
		render(data);
	}
}
