#include "../includes/map_editor.h"

void    set_values_for_parameters(t_character *chars)
{
    //param0: wall height
    chars->param0_choice0 = '#';
    chars->param0_choice1 = '1';
    chars->param0_choice2 = '2';
    chars->param0_choice3 = '3';
    chars->param0_choice4 = '4';
    chars->param0_choice5 = '5';
    //param1: texture
    chars->param1_choice0 = 'A';
    chars->param1_choice1 = 'B';
    chars->param1_choice2 = 'C';
    chars->param1_choice3 = 'D';
    //param2: transparency
    chars->param2_choice0 = 'F';
    chars->param2_choice1 = 'T';
    chars->param2_choice2 = 'P';
    //param3: entity
    chars->param3_choice0 = 'p';
    chars->param3_choice1 = 'm';
}
