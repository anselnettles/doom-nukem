/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:40:37 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/06 16:13:10 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"
#define NUMBER 7

int	error(int code)
{
	const char	*error_message[NUMBER];

	error_message[0] = T_ORANGE "Usage: " T_NUL "./" NAME
		T_ORANGE " | " T_NUL "./" NAME T_RED " <file.dn>" T_NUL;
	error_message[1] = T_RED "Error: No file applied for editor." T_NUL;
	error_message[2] = T_RED "Error: Not a '.dn' level file." T_NUL;
	error_message[3] = T_RED "Error: File open failure." T_NUL;
	error_message[4] = T_RED "Error: File read failure." T_NUL;
	error_message[5] = T_RED "Error: File too large." T_NUL;
	error_message[6] = T_RED "Error: File close failure." T_NUL;
	write(1, error_message[code], ft_strlen(error_message[code]));
	return (ERROR);
}
