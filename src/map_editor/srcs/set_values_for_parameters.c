#include "../../src/drowning.h"

/*
    Hard-coded map[][][x] values.
*/
void    set_values_for_parameters(t_character *chars)
{
    //param0: wall height
    chars->param0_choice0 = '#';
    chars->param0_choice1 = '1';
    chars->param0_choice2 = '2';
    chars->param0_choice3 = '3';
    chars->param0_choice4 = '4';
    chars->param0_choice5 = '5';
    chars->param0_choice6 = '6';
    chars->param0_choice7 = '7';
    chars->param0_choice8 = '8';
    chars->param0_choice9 = '.';
    //param1: texture
    chars->param1_choice0 = 'a';
    chars->param1_choice1 = 'b';
    chars->param1_choice2 = 'c';
    chars->param1_choice3 = '.';
    //param2: 45 degree, x - y
    chars->param2_choice0 = '/';
    chars->param2_choice1 = '\\';
    chars->param2_choice2 = '>';
    chars->param2_choice3 = '<';
    chars->param2_choice4 = '.';
    //param3: entity
    chars->param3_choice0 = 'S';    //player_start
    chars->param3_choice1 = 'G';    //goal
    chars->param3_choice2 = 'M';    //monster1
    chars->param3_choice3 = 'N';    //monster2
    chars->param3_choice4 = 'I';    //item1
    chars->param3_choice5 = 'J';    //item2
    chars->param3_choice6 = 'K';    //item3
    chars->param3_choice7 = '.';
    //param4: secret
    chars->param4_choice0 = 'R';
    chars->param4_choice1 = '*';
    chars->param4_choice2 = '.';
}
