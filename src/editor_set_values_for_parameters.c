/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_set_values_for_parameters.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:39:55 by tturto            #+#    #+#             */
/*   Updated: 2023/03/02 22:24:58 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	# = full wall
	1 - 8 = percentage of full wall
*/
static void	param0_wall_height(t_character *chars)
{
	chars->param0_choice0 = '#';
	chars->param0_choice1 = '1';
	chars->param0_choice2 = '2';
	chars->param0_choice3 = '3';
	chars->param0_choice4 = '4';
	chars->param0_choice5 = '5';
	chars->param0_choice6 = '6';
	chars->param0_choice7 = '7';
	chars->param0_choice8 = '8';
	chars->param0_choice9 = '9';
	chars->param0_choice10 = '.';
	chars->param0_choice11 = '0';
}

static void	param1_texture(t_character *chars)
{
	chars->param1_choice0 = 'a';
	chars->param1_choice1 = 'b';
	chars->param1_choice2 = 'c';
	chars->param1_choice3 = '.';
}

static void	param2_special_walls(t_character *chars)
{
	chars->param2_choice0 = '/';
	chars->param2_choice1 = '\\';
	chars->param2_choice2 = '>';
	chars->param2_choice3 = '<';
	chars->param2_choice4 = '.';
}

/*
	'X' = player_start
	'Z' = goal
	'M' = monster1
	'N' = monster2
	'I' = item1
	'J' = item2
	'K' = item3
	'R' = secret
	'*' = special_element
*/
static void	param3_and_4_entity_secret(t_character *chars)
{
	chars->param3_choice0 = 'X';
	chars->param3_choice1 = 'Z';
	chars->param3_choice2 = 'M';
	chars->param3_choice3 = 'N';	// remove. most likely monster2 will not be used
	chars->param3_choice4 = 'I';
	chars->param3_choice5 = 'J';
	chars->param3_choice6 = 'K';
	chars->param3_choice7 = '.';
	chars->param4_choice0 = 'R';
	chars->param4_choice1 = '*';
	chars->param4_choice2 = '.';
	chars->param4_choice3 = '\'';
	chars->param4_choice4 = '\"';
}

/*
    Hard-coded map[][][x] values.
	'.' = no element
*/
void	set_values_for_parameters(t_character *chars)
{
	param0_wall_height(chars);
	param1_texture(chars);
	param2_special_walls(chars);
	param3_and_4_entity_secret(chars);
}
