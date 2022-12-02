/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/30 17:22:04 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

int	intersect(t_intersect &i)
{
	i.x = (vxs(vxs(i.x1, i.y1, i.x2, i.y2), (i.x1) - (i.x2),
			vxs(i.x3, i.y3, i.x4, i.y4), (i.x3) - (i.x4))
		/ vxs((i.x1) - (i.x2), (i.y1) - (i.y2),
			(i.x3) - (i.x4), (i.y3) - (i.y4)));
	i.y = (vxs(vxs(i.x1, i.y1, i.x2, i.y2), (i.y1) - (i.y2),
			vxs(i.x3, i.y3, i.x4, i.y4), (i.y3) - (i.y4))
		/ vxs((i.x1) - (i.x2), (i.y1) - (i.y2),
			(i.x3) - (i.x4), (i.y3) - (i.y4)));
}
