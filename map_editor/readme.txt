Left off: map_editor, row 39-41

1)OK  make parameter modification column dependant on the parameter (1 x n)
2)  map to contain W, P, M, T - to indicate Wall, Player, Mob, is_transparent
2)  save modification to buffer
3)  continue/finish editing
    A)  if continue, loop editing_program
    B)  if finish
        B1) validate map
            B11) if NOT ok, loop editing_program
            B12) if ok, transfer buffer to ***map

renaming suggestions:
    get_m1_pressed_map_element => is_mouse_in_grid1_grid2   //note that this functions already update to struct the grid_x/y
    get_m1_pressed_img_grid_element => is_mouse_in_grid3   //note that this functions already update to struct the grid_x/y

-------------------------------------------------------------------------------
map[x][y][z]
    x/y =   coordinates
    z   =   parameter indicating what the coordinate point contains.
            [][][0] = wall height, [][][1] = wall texture type... [][][n]

0 (wall height)
    0   = abyss (=bottomless pit)
    1   = 50% of a cube     
    2   = 100% of a cube  
    3   = ...
    4   = ...
    #   = full wall   
1 (texture type)
    A   =   texture1
    B   =   texture2
    C   =   texture3
    D   =   texture4
2 (texture transparency)
    F   = not transparent
    T   = fully transparent
    P   = pre-set transparency value (e.g. 50 %)
3 (entity)
    s   = player_spawn
    m   = enemy_spawn
    
----------------------------------------------------------------------------
#### #A## #A## #B## ####
#B## 2A.. 0... 0..m #C##
#BT# 1A.. 0... 0... #C##
#AT# 0... 0... 5B.. #A##
#A## 0... 0..s 5B.. #A##
#### #A## #A## #A## ####

XXXX
||||->  s   = player_start / m = spawn_mob      
|||->   O-U = texture transparency value
||->    A-G = texture type
|->     #   = full wall / < 1_digit_number > = floor height

'.' = empty, no parameter value

----------------------------------------------------------------------------

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

