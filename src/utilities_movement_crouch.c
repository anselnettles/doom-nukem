/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_movement_crouch.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 17:25:12 by tturto            #+#    #+#             */
/*   Updated: 2023/03/13 17:25:19 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	crouch(t_drown *data)
{
	if (data->system.keyboard_state[SDL_SCANCODE_C])
		data->player.base_height = 16;
	else
		data->player.base_height = 32;
}
