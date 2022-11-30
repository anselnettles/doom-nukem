/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:50:06 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/30 13:06:06 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

/*Return the greater of the applied values*/
int	max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

/*Return the smaller of the applied values*/
int	min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

/*Clamp value into set range.*/
int	clamp(int a, int lower, int upper)
{
	return (min(max(a, lower), upper));
}
