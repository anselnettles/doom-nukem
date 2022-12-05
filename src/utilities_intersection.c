/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_intersection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:58:00 by aviholai          #+#    #+#             */
/*   Updated: 2022/12/05 19:24:32 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

void	intersect(t_intersect *i)
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
