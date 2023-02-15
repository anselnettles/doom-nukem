#include "../includes/map_editor.h"

/*
    insert comments
*/
//set selected choice of a selected parameter into map_temp: 
//(t_map).map_temp[map_y][map_x][param_to_modify] = (t_character).paramN_choiceM;
static void value_of_parameter_4(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param4_choice0;
    }
    if (data->selection_index == 1)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param4_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param4_choice2;
    }
}

static void value_of_parameter_3(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice0;
    }
    if (data->selection_index == 1)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice2;
    }
    if (data->selection_index == 3)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice3;
    }
    if (data->selection_index == 4)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice4;
    }
    if (data->selection_index == 5)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice5;
    }
    if (data->selection_index == 6)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice6;
    }
    if (data->selection_index == 7)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param3_choice7;
    }
}

static void value_of_parameter_2(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param2_choice0;
    }
    if (data->selection_index == 1)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param2_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param2_choice2;
    }
    if (data->selection_index == 3)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param2_choice3;
    }
    if (data->selection_index == 4)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param2_choice4;
    }
}

static void value_of_parameter_1(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param1_choice0;
    }
    if (data->selection_index == 1)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param1_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param1_choice2;
    }
    if (data->selection_index == 3)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param1_choice3;        
    }
}

static void    value_of_parameter_0(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice0;
    }
    if (data->selection_index == 1)
    {    
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice2;
    }
    if (data->selection_index == 3)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice3;
    }
    if (data->selection_index == 4)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice4;
    }
    if (data->selection_index == 5)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice5;
    }
    if (data->selection_index == 6)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice6;
    }
    if (data->selection_index == 7)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice7;
    }
    if (data->selection_index == 8)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice8;
    }
    if (data->selection_index == 9)
    {
        data->map_temp[data->map_y][data->map_x][data->param_to_modify]
            = chars->param0_choice9;
    }
}

//  Function saves the pre-defined char (e.g. param0_choice0 == 'A') to map_temp[map_y][map_x][param_to_modify]
void    select_new_param_value(t_editor *editor, t_map *data, t_character *chars)
{
    if (editor->event.type == SDL_MOUSEBUTTONDOWN)
    {
        printf("img3: map_x & map_y (are still): %d & %d\n", data->map_x, data->map_y);
        printf("img3: param_to_modify (is still): %d\n", data->param_to_modify);
        if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 0) 
            value_of_parameter_0(data, chars);
        if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 1) 
            value_of_parameter_1(data, chars);
        if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 2) 
            value_of_parameter_2(data, chars);
        if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 3) 
            value_of_parameter_3(data, chars);
        if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 4) 
            value_of_parameter_4(data, chars);
    }
}
