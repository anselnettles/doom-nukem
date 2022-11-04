/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:40:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/04 18:05:28 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#define NUMBER 1

int	error(int code)
{
	const char	*error_message[NUMBER];

	error_message[0] = T_ORANGE "Usage: " T_NUL "./" NAME
		T_ORANGE " | " T_NUL "./" NAME T_RED " <file.dn>" T_NUL;
	write(1, error_message[code], ft_strlen(error_message[code]));
	return (1);
}
