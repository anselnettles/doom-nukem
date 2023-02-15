#include "drowning.h"

/* ---- = followed by undone part
3D:
!    texture[3][64][64]                         //change to 4 x 2D
@    drown->sprite.weed[3][48][20]
$    drown->storyboard.beginning[3][642][480]
%    drown->storyboard.bad_end[3][642][480]
^    drown->storyboard.good_end[3][642][480]
&    drown->sprite.bottle[3][64][64]
~    drown->sprite.ammo[3][12][12]
z    drown->sprite.right_arm[3][238][250]
-    drown->sprite.harpoon[6][64][64]
+    drown->sprite.goal[6][128][64]
]    drown->sprite.timer[?][20][20]
[    drown->sprite.left_arm[?][?][?]

2D:
`    drown->storyboard.title_screen[642][480]
X    drown->sprite.foliage[128][128]
:    drown->sprite.moss[60][60]
Y    drown->sprite.letters[20][728]
Z    drown->txt.skybox[64][128]

4D:
    drown->sprite.monster[8][3][128][128]

    drown->txt.texture_d[64][64] : Crate.
    drown->txt.texture_c[64][64] : Pillar.
    drown->txt.texture_b[64][64] : Wall.
    drown->txt.texture_a[64][64] : Floor.
*/

// part of the textures not in struct yet (under work)

static void array_selection(char *arr_selection, char *str, t_index *index, t_gfx *gfx)
{
    uint32_t            hex_value;
//3D elements. Same logic as for other dimensions
    if (strcmp(arr_selection, "texture") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->texture[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "weed") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->weed[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "beginning") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->beginning[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "bad_end") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->bad_end[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "good_end") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->good_end[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "bottle") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->bottle[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "ammo") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->ammo[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "right_arm") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->right_arm[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "harpoon") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->harpoon[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "goal") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->goal[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "timer") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->timer[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "left_arm") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->left_arm[index->i2][index->i1][index->i0] = hex_value;
    }
//2D section
    else if (strcmp(arr_selection, "title_screen") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->title_screen[index->i1][index->i0] = hex_value;
    }
        else if (strcmp(arr_selection, "foliage") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->foliage[index->i1][index->i0] = hex_value;
    }
        else if (strcmp(arr_selection, "moss") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->moss[index->i1][index->i0] = hex_value;
    }
        else if (strcmp(arr_selection, "letters") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->letters[index->i1][index->i0] = hex_value;
    }
        else if (strcmp(arr_selection, "skybox") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        drown->gfx.texture.skybox[index->i1][index->i0] = hex_value;
    }
}

static void parse_textures_3D(char limiter, t_gfx *gfx, char *buf, char *arr_selection)
{
    char    str[11];
    int     a;
    int     k;
    t_index index;

    k = 0;
    //Start: roll over map data, until first limiter = '!' 
    while (buf[k] != limiter)
        k++;
    k++;
    //End: roll over map data, until first limiter = '!' 
    
    index.i2 = 0;
    a = 0;
    while (buf[k] != limiter)
    {
        while (buf[k] != '{')
            k++;
        if (buf[k] == '{')
            k++;
        index.i0 = 0;                 //reset "x"
        index.i1 = 0;                 //reset "y"
        while (buf[k] != '}')         //loops per texture
        {
            a = 0;
            while (buf[k] != ',' && buf[k] != '}')
            {
                str[a] = buf[k];
                a++;
                k++;
            }
            str[a] = '\0';
            array_selection(arr_selection, str, &index, gfx);
            if (buf[k] == '}')
            {
                index.i2++;
                k++;
                break ;
            }
            if (buf[k] == ',')
            {
                index.i0++;
                k++;        
            }
            if (buf[k] == ' ')
                k++;
            if (buf[k] == '\n')
            {
                index.i0 = 0;         //reset "x"
                index.i1++;
                k++;
            }
        }
    }
}

static void parse_textures_2D(char limiter, t_gfx *gfx, char *buf, char *arr_selection)
{
    char    str[11];
    int     a;
    int     k;
    t_index index;

    k = 0;
    //Start: roll over map data, until first limiter = '!' 
    while (buf[k] != limiter)
        k++;
    k++;
    //End: roll over map data, until first limiter = '!' 
    
    index.i2 = 0;   //this is not used in 2D module, here only due to using same index struct as in 3D module
    a = 0;
    while (buf[k] != limiter)
    {
        while (buf[k] != '{')
            k++;
        if (buf[k] == '{')
            k++;
        index.i0 = 0;                 //reset "x"
        index.i1 = 0;                 //reset "y"
        while (buf[k] != '}')         //loops per texture
        {
            a = 0;
            while (buf[k] != ',' && buf[k] != '}')
            {
                str[a] = buf[k];
                a++;
                k++;
            }
            str[a] = '\0';
            array_selection(arr_selection, str, &index, gfx);
            if (buf[k] == '}')
            {
                k++;
                break ;
            }
            if (buf[k] == ',')
            {
                index.i0++;
                k++;        
            }
            if (buf[k] == ' ')
                k++;
            if (buf[k] == '\n')
            {
                index.i0 = 0;         //reset "x"
                index.i1++;
                k++;
            }
        }
    }  
}

static void parse_images(char *buf, t_gfx *gfx)
{
//3 dimensional array parse
    parse_textures_3D('!', gfx, buf, "texture");    
    parse_textures_3D('@', gfx, buf, "weed");
    parse_textures_3D('$', gfx, buf, "beginning");
    parse_textures_3D('%', gfx, buf, "bad_end");
    parse_textures_3D('^', gfx, buf, "good_end");
    parse_textures_3D('&', gfx, buf, "bottle");
    parse_textures_3D('~', gfx, buf, "ammo");
    parse_textures_3D('z', gfx, buf, "right_arm");
    parse_textures_3D('-', gfx, buf, "harpoon");
    parse_textures_3D('+', gfx, buf, "goal");
    parse_textures_3D(']', gfx, buf, "timer");
    parse_textures_3D('[', gfx, buf, "left_arm");

//2 dimensional array parse
    parse_textures_2D('`', gfx, buf, "title_screen");
    parse_textures_2D('X', gfx, buf, "foliage");
    parse_textures_2D(':', gfx, buf, "moss");
    parse_textures_2D('Y', gfx, buf, "letters");
    parse_textures_2D('Z', gfx, buf, "skybox");

//4 dimensional array parse
/*
<symbol>    drown->sprite.monster[8][3][128][128]
*/    

}

//limiters of image file: !, %, $, ... will not be made into global list. Parser will be left shit like this: limiters inside the function
void    parse_map_file_to_arrays(char *buf, t_gfx *gfx)
{
    parse_images(buf, gfx);

    // parse_sprites(buf, editor);
    // ...
    // return (1);
}