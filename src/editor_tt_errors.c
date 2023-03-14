/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_tt_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:18:42 by tturto            #+#    #+#             */
/*   Updated: 2023/03/14 16:41:31 by aviholai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

void	tt_errors(char *error_msg)
{
	while (*error_msg != '\0')
	{
		write(1, error_msg, 1);
		error_msg++;
	}
	write(1, "\n", 1);
}

void	tt_errors_exit(char *error_msg, t_drown *d)
{
	while (*error_msg != '\0')
	{
		write(1, error_msg, 1);
		error_msg++;
	}
	write(1, "\n", 1);
	quit_program(d);
}
