/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_set_values_for_parameters.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tturto <tturto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:39:55 by tturto            #+#    #+#             */
/*   Updated: 2023/03/10 18:39:10 by tturto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drowning.h"

/*
	# = full wall
	0 - 9 = percentage of the full wall, 0 being the lowest
*/
static void	param0_wall_height(t_character *chars)
{
	chars->param0_choice0 = '.';
	chars->param0_choice1 = '#';
	chars->param0_choice2 = '9';
	chars->param0_choice3 = '8';
	chars->param0_choice4 = '7';
	chars->param0_choice5 = '6';
	chars->param0_choice6 = '5';
	chars->param0_choice7 = '4';
	chars->param0_choice8 = '3';
	chars->param0_choice9 = '2';
	chars->param0_choice10 = '1';
	chars->param0_choice11 = '0';
}

static void	param1_texture(t_character *chars)
{
	chars->param1_choice0 = '.';
	chars->param1_choice1 = 'a';
	chars->param1_choice2 = 'b';
	chars->param1_choice3 = 'c';
}

static void	param2_special_walls(t_character *chars)
{
	chars->param2_choice0 = '.';
	chars->param2_choice1 = '/';
	chars->param2_choice2 = '\\';
	chars->param2_choice3 = '>';
	chars->param2_choice4 = '<';
}

/*
	'.'	= empty
	'X' = player_start
	'Z' = goal
	'@' = monster1
	'$' = item1		//air bottle
	'J' = item2		//harpoon
	'R' = secret
	'*' = special_element0
	''' = special_element1
	'"' = special_element2
*/
static void	param3_and_4_entity_secret(t_character *chars)
{
	chars->param3_choice0 = '.';
	chars->param3_choice1 = 'X';
	chars->param3_choice2 = 'Z';
	chars->param3_choice3 = '@';
	chars->param3_choice4 = '$';
	chars->param3_choice5 = 'J';
	chars->param4_choice0 = '.';
	chars->param4_choice1 = 'R';
	chars->param4_choice2 = '*';
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
