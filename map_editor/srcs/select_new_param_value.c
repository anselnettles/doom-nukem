#include "../includes/map_editor.h"
//!!! setting into temp: struct->map_temp[map_x][map_y][param_to_modify] = struct.param0_choice0;

/* Do not remove. Individual parameter_value_of_parameter_n for each parameter: */

static void value_of_parameter_3(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param3_choice0;
    }
    if (data->selection_index == 1)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param3_choice1;
    }
}
static void value_of_parameter_2(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param2_choice0;
    }
    if (data->selection_index == 1)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param2_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param2_choice2;
    }
}
static void value_of_parameter_1(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param1_choice0;
    }
    if (data->selection_index == 1)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param1_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param1_choice2;
    }
    if (data->selection_index == 3)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param1_choice3;        
    }
}

//  Function saves the pre-defined char (e.g. param0_choice0 == 'A') to map_temp[map_x][map_y][param_to_modify]
static void    value_of_parameter_0(t_map *data, t_character *chars)
{
    if (data->selection_index == 0)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param0_choice0;
    }
    if (data->selection_index == 1)
    {    
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param0_choice1;
    }
    if (data->selection_index == 2)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param0_choice2;
    }
    if (data->selection_index == 3)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param0_choice3;
    }
    if (data->selection_index == 4)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param0_choice4;
    }
    if (data->selection_index == 5)
    {
        data->map_temp[data->map_x][data->map_y][data->param_to_modify]
            = chars->param0_choice5;
    }
}
// remove t_editor_images if not used
void    select_new_param_value(t_editor *editor, t_map *data, t_character *chars, t_editor_images *images)
{
    // selection_index_x and selection_y form selection_index
    // selection_index_x is always 0, as selection column count is 1 
    if (editor->event.type == SDL_MOUSEBUTTONDOWN)
    {
        printf("img3: map_x & map_y (are still): %d & %d\n", data->map_x, data->map_y);
        printf("img3: param_to_modify (is still): %d\n", data->param_to_modify);
        if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 0) 
            value_of_parameter_0(data, chars);
        else if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 1) 
            value_of_parameter_1(data, chars);
        else if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 2) 
            value_of_parameter_2(data, chars);
        else if (editor->event.button.button == SDL_BUTTON_LEFT && data->param_to_modify == 3) 
            value_of_parameter_3(data, chars);
    }
    

}
