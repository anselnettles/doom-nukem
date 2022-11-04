/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:40:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/04 21:00:11 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#define NUMBER 3

int	error(int code)
{
	const char	*error_message[NUMBER];

	error_message[0] = T_ORANGE "Usage: " T_NUL "./" NAME
		T_ORANGE " | " T_NUL "./" NAME T_RED " <file.dn>" T_NUL;
	error_message[1] = T_RED "Error: No file applied for editor." T_NUL;
	error_message[2] = T_RED "Error: Not a '.dn' level file." T_NUL;
	write(1, error_message[code], ft_strlen(error_message[code]));
	return (1);
}
