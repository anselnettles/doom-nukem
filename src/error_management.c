/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:40:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 16:02:30 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	error(int code)
{
	const char	*error_message[15];

	error_message[0] = T_ORANGE "Usage: " T_NUL "./" NAME
		T_ORANGE " | " T_NUL "./" NAME T_RED " <file.dn> " T_NUL;
	error_message[1] = T_RED "Error: No file applied for parsing. " T_NUL;
	error_message[2] = T_RED "Error: Not a valid (.dn) level file. " T_NUL;
	error_message[3] = T_RED "Error: File open failure. File not found. " T_NUL;
	error_message[4] = T_RED "Error: File read failure. " T_NUL;
	error_message[5] = T_RED "Error: File too large. " T_NUL;
	error_message[6] = T_RED "Error: File close failure. " T_NUL;
	error_message[7] = T_RED " is an illegal character in map file. " T_NUL;
	error_message[8] = T_RED "Error: File map aspect is inconsistent. " T_NUL;
	error_message[9] = T_RED "Error: Map file WALL has a bad parameter. " T_NUL;
	error_message[10] = T_RED "Error: Level editor failure. " T_NUL;
	error_message[11] = T_RED "\n Error: SDL library failure. " T_NUL;
	error_message[12] = T_RED "Error: Player initialization failure. ";
	error_message[13] = T_RED "Error: Graphics rendering failure. " T_NUL;
	error_message[14] = T_RED "Error: Texture initialization failure. " T_NUL;
	write(1, error_message[code], ft_strlen(error_message[code]));
	return (ERROR);
}
