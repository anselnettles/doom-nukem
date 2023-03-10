/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_img3_texts.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:48:51 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 16:38:42 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	The called functions are located as non-static
		in editor_utilities_img3_texts.c
*/
void	img3_texts(t_drown *data, int param_to_modify)
{
	int	x;
	int	y;

	x = data->editor.images.img3_x_min + (IMG3_CATHETUS * 0.05);
	y = data->editor.images.img_y_min + (IMG3_CATHETUS * 0.5);
	if (param_to_modify == 0)
		text_param_selection_0(x, y, data);
	else if (param_to_modify == 1)
		text_param_selection_1(x, y, data);
	else if (param_to_modify == 2)
		text_param_selection_2(x, y, data);
	else if (param_to_modify == 3)
		text_param_selection_3(x, y, data);
	else if (param_to_modify == 4)
		text_param_selection_4(x, y, data);
}
