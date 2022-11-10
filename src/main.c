/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:24:05 by aviholai          #+#    #+#             */
/*   Updated: 2022/11/10 17:33:10 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "library.h"

// Begin of program. Run the binary with no arguments to launch the game.
// Run the binary with a single argument to launch the level editor.

int	main(int argc, char **argv)
{
	t_rain	rain;

	ft_bzero(&rain, sizeof(t_rain));
	rain.system.user_request = argc;
	rain.editor.file = argv[1];
	if (rain.system.user_request == RUN_GAME)
	{
		if (graphic_interface(&rain) == ERROR)
			return (ERROR);
	}
	else if (rain.system.user_request == RUN_LEVEL_EDITOR)
	{
		if (read_file(&rain) == ERROR)
			return (ERROR);
	}
	else
		return (error(BAD_ARGS));
	return (0);
}
