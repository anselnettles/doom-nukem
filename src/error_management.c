/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:40:37 by aviholai          #+#    #+#             */
/*   Updated: 2023/01/27 18:53:27 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

int	error(int code)
{
	const char	*error_message[15];

	error_message[0] = T_ORANGE "Usage: " T_NUL "./" NAME "\n" T_NUL;
	error_message[1] = T_RED "Error: No file applied for parsing.\n" T_NUL;
	error_message[2] = T_RED "Error: Not a valid (.dn) level file.\n" T_NUL;
	error_message[3] = T_RED "Error: File open fail. File not found.\n" T_NUL;
	error_message[4] = T_RED "Error: File read failure.\n" T_NUL;
	error_message[5] = T_RED "Error: File too large.\n" T_NUL;
	error_message[6] = T_RED "Error: File close failure.\n" T_NUL;
	error_message[7] = T_RED " is an illegal character in map file.\n" T_NUL;
	error_message[8] = T_RED "Error: File map aspect is inconsistent.\n" T_NUL;
	error_message[9] = T_RED "Error: Map WALL has a bad parameter.\n" T_NUL;
	error_message[10] = T_RED "Error: Level editor failure.\n" T_NUL;
	error_message[11] = T_RED "\n Error: SDL library failure.\n" T_NUL;
	error_message[12] = T_RED "Error: Player initialization failure.\n";
	error_message[13] = T_RED "Error: Graphics rendering failure.\n" T_NUL;
	error_message[14] = T_RED "Error: Texture initialization failure.\n" T_NUL;
	write(1, error_message[code], ft_strlen(error_message[code]));
	return (ERROR);
}
