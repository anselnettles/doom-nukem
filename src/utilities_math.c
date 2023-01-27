/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities_math.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 16:04:35 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

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

//Returns square root of the given value.
float	square_root(float nb)
{
	float	sqrt;
	float	temp;

	sqrt = nb / 2;
	temp = 0;
	while (sqrt != temp)
	{
		temp = sqrt;
		sqrt = ((nb / temp) + temp) / 2;
	}
	return (sqrt);
}

//Converts degrees to radians.
double	deg_to_rad(double degrees)
{
	return (degrees * (double)M_PI / 180.0);
}
