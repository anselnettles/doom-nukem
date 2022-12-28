/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2022/12/28 10:00:02 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

//Return the greater of the applied values
int	max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

//Return the smaller of the applied values
int	min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

//Clamp value into set range.
int	clamp(int a, int lower, int upper)
{
	return (min(max(a, lower), upper));
}

double	deg_to_rad(double degrees)
{
	return (degrees * (double)M_PI / 180.0);
}

/*
//Determine whether the two number ranges overlap.
int	overlap(int a0, int a1, int b0, int b1)
{
	return (min(a0, a1) <= max(b0, b1) && min(b0, b1) <= max(a0, a1));
}
*/

/*
//Vector cross product.
int	vxs(int x0, int y0, int x1, int y1)
{
	return ((x0) * (y1) - (x1) * (y0));
}
*/
