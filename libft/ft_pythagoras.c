/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pythagoras.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:42:28 by tpaaso            #+#    #+#             */
/*   Updated: 2023/01/05 13:32:49 by tpaaso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

float     ft_pythagoras(float a, float b, float c)
{
    if (a == 0 || b == 0)
    {
        if (b == 0 && a == 0)
            return (-1);
        if (b != 0 && a == 0)
        {
            a = b;
            b = 0;
        }
        if (c != 0)
            return(sqrtf((c * c) - (a * a)));
    }
    if (c == 0 && a != 0 && b != 0)
        return(sqrtf((a * a) + (b * b)));
    return(-1);
}
