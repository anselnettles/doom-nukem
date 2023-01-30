/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_system.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/30 16:24:32 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

//	Sdl_loop() keeps Simple Direct MediaLayer's PollEvent constantly
//	running and checks for control calls while rerendering the graphical
//	view.
void	sdl_loop(t_drown *data)
{
	while (data->play_state == PLAY)
	{
		while(SDL_PollEvent(&data->event) != 0)
		{
			if (data->event.type == SDL_QUIT)
				data->play_state = EXIT;
			else if (data->event.type == SDL_KEYDOWN)
				deal_key(data->event.key.keysym.sym, data);
			else if (data->event.type == SDL_MOUSEMOTION)
				deal_mouse(data);
		}
		render(data);
	}
}
