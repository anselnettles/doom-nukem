/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utilities_img3_texts.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:34:50 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 16:37:32 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
    These functions are only called by img3_texts().
*/
void	text_param_selection_4(int x, int y, t_drown *data)
{
	gfx_write(x, y, &data->gfx, "EMPTY");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "ONE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "TWO");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "THREE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "FOUR");
}

void	text_param_selection_3(int x, int y, t_drown *data)
{
	gfx_write(x, y, &data->gfx, "EMPTY");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "START");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "GOAL");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "MONSTER");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "BOTTLE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "HARPOON");
}

void	text_param_selection_2(int x, int y, t_drown *data)
{
	gfx_write(x, y, &data->gfx, "EMPTY");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "SW");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "SE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "NW");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "NE");
}

void	text_param_selection_1(int x, int y, t_drown *data)
{
	gfx_write(x, y, &data->gfx, "EMPTY");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "A");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "B");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "C");
}

void	text_param_selection_0(int x, int y, t_drown *data)
{
	gfx_write(x, y, &data->gfx, "EMPTY");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "FULL");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "NINE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "EIGHT");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "SEVEN");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "SIX");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "FIVE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "FOUR");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "THREE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "TWO");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "ONE");
	y = y + (IMG3_CATHETUS + 1);
	gfx_write(x, y, &data->gfx, "ZERO");
}
