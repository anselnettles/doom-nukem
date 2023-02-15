---------------------------------------------------------------------------------
Continue: 
---------------------------------------------------------------------------------
OK  - change file names to editor_<filename>
    - change topis **map to **map2
    - do until main: "if (render(&data) == ERROR)"
    - remove init from editor (it is in main)    
    - bzero sets 0 to all structs, all params. Consider removing Compound Literals
    
    - parser not aligned with structs
    
    
---------------------------------------------------------------------------------
Fix notes:
---------------------------------------------------------------------------------

    0) param6 grid element is drawn in img2 (remove later; element_count must equal to param_count)
    2) Non-NL ending map file segfaults. Modify validate_buffer_format() || read_map()
    Buffer read:

        /frame$ ./a.out testbufs/F-3-MissNL 
        read OK -->
        count_buffer_data: buffer_1_set_validatio OK -->
        count_buffer_data: buffer_row_len_validation OK -->
        count_buffer_data OK -->
        validate OK -->
        validate_buffer_format return: 1 (1 = OK)

        -> Does buffer_to_3D_map_arr need NL at end?
            -> Modification of read_map.c suggested in validate_buffer_format.count_buffer_data
            -> if works, ignore error message.

    3) legend.c is unused. Remove from repository unless implement it
    5) 1.5M buffer size can be split into mallocs (see teemus instructions)

---------------------------------------------------------------------------------
Progress:
---------------------------------------------------------------------------------
    1)OK    main: copy_map_to_map_temp()    //this will be called after read_map() and looped upon param changes
    2)OK    select_new_param_value()
    3)OK    Keypress='s' to save.
        OK      SAVE should not close any images
        OK      SAVE should be active all the time
        OK      M2 takes back to img1
    4)      It would be good to be able to return to img2 from img3 by clicking a parameter in img2.
            This would then open a new img3 based on the selected parameter in img2.

            It would be good to be able to return to img1 from img2 and img3 by clicking a parameter in img1.
            This would then open a new img2 based on the selected parameter in img1.
            
    5)      validate_buffer()       // merge from home_local
    6)OK    validate_map_temp()     //***map will not be validated, instead, ***map_temp and buf will be. 
    7)      main program needs to re-read mapfile, then re-create ***map (!previous ***map is behind ***map_temp)
    8)      save_file() file management: what is the new file name? same (overwrite)?
    9)      map elements, parameter elements, choice elements --> GUI to correspond data
    10)     legend (M2, s, ESC): 1) TTF extension, 2) image to surface
    11)     save_changes(): edge cases for file management

---------------------------------------------------------------------------------
 ***    Dynamic alterations:
---------------------------------------------------------------------------------
    if increase parameter_count, modify the following files:
        1)  .h -> PARAM_COUNT
        2)  .h -> IMG2_PARAM_ROW
        3)  set_values_for_parameters() //remember alteration in .h
        4)  validate_map_temp()
        5)  select_new_param_value()
        6)  img1_and_img2/param_to_modify()
        7)  img3_to_gui/get_param_row()
    if increase selection_count of a parameter, modify the following files:
        1)  -
        2)  -
        3)  set_values_for_parameters() //remember alteration in .h
        4)  validate_map_temp()
        5)  select_new_param_value()
        6)  img1_and_img2/param_to_modify()
        7)  img3_to_gui/get_param_row()

---------------------------------------------------------------------------------
End:
---------------------------------------------------------------------------------
    unused parameters (functions calls with unnecessarys structs)
    final path: ~/doom-nukem/srcs/map_editor/*.c

-------------------------------------------------------------------------------
Map contents:
-------------------------------------------------------------------------------
map[x][y][z]
    x/y =   coordinates
    z   =   parameter indicating what the coordinate contains.
            [][][0] = wall height, [][][1] = wall texture type... [][][n]
    
    #a/PR 1b>G. 2c\MR #a/PR
    ..... #.>N. .b>KR .....
    #c/I. ..... #c/.. .....
    ..... ..... ..... .....
    !texture_0={0xff8fbecf, 0xff8fbecf, 
    0xff8fbecf, 0xff8fbecf, 
    0xff8fbecf, 0xff8fbecf},
    texture_1={...}!
    ~sprite_arm_right0={...},sprite_arm_right1{...},sprite_arm_right2{...}~
    @sprite_arm_left={...}$@
    ?sprite_weed={...}?
    +sprite_projectile={...}+
    |sprite_monster0={...}|
    $sprite_collectible0={...}$
    &sprite_goal={...}&
    "sprite_breakable={...}"
    %sprite_glass={...}%'\n'

',' separates arrays of same type: texture[0][][], texture[1][][], ... etc

'.' = ignore option during render()

0:  Block height
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

1:  Texture
    chars->param1_choice0 = 'a';
    chars->param1_choice1 = 'b';
    chars->param1_choice2 = 'c';
    chars->param1_choice3 = '.';

2:  "45 degree"
    chars->param2_choice0 = '/';
    chars->param2_choice1 = '\\';
    chars->param2_choice2 = '>';
    chars->param2_choice3 = '<';
    chars->param2_choice4 = '.';

3:  Entity
    chars->param3_choice0 = 'P';    //player_start
    chars->param3_choice1 = 'G';    //goal
    chars->param3_choice2 = 'M';    //monster1
    chars->param3_choice3 = 'N';    //monster2
    chars->param3_choice4 = 'I';    //item1
    chars->param3_choice5 = 'J';    //item2
    chars->param3_choice6 = 'K';    //item3
    chars->param3_choice7 = '.';

4:  Special
    chars->param4_choice0 = 'R';    //"Secret path". Contains a hard-coded transparency value.
                                    //  Renders a ceiling on top of the i0(0)_wall_height_choice (WHC).
                                    //  Distance between WHC - Roof = hard-coded, e.g. 1 cube
    chars->param4_choice1 = '*';    //"Pillar to infinity"
    chars->param4_choice2 = '.';

---------------------------------------------------------------------------------
Map Contents (developed):
---------------------------------------------------------------------------------
Ehdotus nr 2:

i0(0) = wall height     (# & 1 - 9)
i0(1) = texture ref.    (a - c)
i0(2) = 45deg           ( /, \, <, > )
i0(3) = entities        (player_start, goal, sprites, mobs…)
i0(4) = salareitti      ( R = contains a hard-coded transparency value, renders a roof on top of the i0(0) wall_height choice (WHC).
                        Distance between WHC - Roof = hard-coded, e.g. 1 cube)
                        '*' = pillar)
                        
Each parameter contain '.', which indicates in code "skip".

---------------------------------------------------------------------------------
Enhancement options:
---------------------------------------------------------------------------------

typedef struct s_map
{
    int height;
    int floorheight
    char texture;
    char ttv;
    void * mob;
    float *dir;
} t_map;

"map[y][x]->height"

t_map **map;

map = (t_map **)malloc(sizeof(t_map *) * y);
while (map[y] = (t_map *)malloc(sizeof(t_map) * x)
    y++;

-----------------------------------------------------------------

