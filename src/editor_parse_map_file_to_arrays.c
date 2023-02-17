#include "drowning.h"

static void array_selection(char *arr_selection, char *str, t_index *index, t_gfx *gfx)
{
    uint32_t            hex_value;
//2D arrays
    if (strcmp(arr_selection, "texture_a") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->txt.texture_a[index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "texture_b") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->txt.texture_b[index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "texture_c") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->txt.texture_c[index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "texture_d") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->txt.texture_d[index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "skybox") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->txt.skybox[index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "letters") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->sprite.letters[index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "bubble") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->sprite.bubble[index->i1][index->i0] = hex_value;
    }
//3D arrays
    else if (strcmp(arr_selection, "right_arm") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->sprite.right_arm[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "harpoon") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->sprite.harpoon[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "bottle") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->sprite.bottle[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "timer") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->sprite.timer[index->i2][index->i1][index->i0] = hex_value;
    }
    else if (strcmp(arr_selection, "ammo") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        gfx->sprite.ammo[index->i2][index->i1][index->i0] = hex_value;
    }
    /*else if (strcmp(arr_selection, "goal") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->goal[index->i2][index->i1][index->i0] = hex_value;
    }*/
    /*else if (strcmp(arr_selection, "left_arm") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->left_arm[index->i2][index->i1][index->i0] = hex_value;
    }*/
//2D section
    /*else if (strcmp(arr_selection, "title_screen") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->title_screen[index->i1][index->i0] = hex_value;
    }*/
    /*else if (strcmp(arr_selection, "foliage") == 0)
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
    }*/
    /*else if (strcmp(arr_selection, "weed") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->weed[index->i2][index->i1][index->i0] = hex_value;
    }*/
    /*else if (strcmp(arr_selection, "beginning") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->beginning[index->i2][index->i1][index->i0] = hex_value;
    }*/
    /*else if (strcmp(arr_selection, "bad_end") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->bad_end[index->i2][index->i1][index->i0] = hex_value;
    }*/
    /*else if (strcmp(arr_selection, "good_end") == 0)
    {
        hex_value = (uint32_t)strtol(str, NULL, 16);
        hex_value = swap_red_with_blue(hex_value);
        editor->good_end[index->i2][index->i1][index->i0] = hex_value;
    }*/
}

static void parse_textures_3D(char limiter, t_gfx *gfx, char *buf, char *arr_selection)
{
    char    str[11];
    int     a;
    int     k;
    t_index index;

    k = 0;
    while (buf[k] != limiter)
        k++;
    k++;
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
    while (buf[k] != limiter)
        k++;
    k++;
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
//2 dimensional array parse
    parse_textures_2D('A', gfx, buf, "texture_a");   
    parse_textures_2D('B', gfx, buf, "texture_b");   
    parse_textures_2D('C', gfx, buf, "texture_c");   
    parse_textures_2D('D', gfx, buf, "texture_d");
    parse_textures_2D('E', gfx, buf, "skybox");
    parse_textures_2D('G', gfx, buf, "letters");
    parse_textures_2D('K', gfx, buf, "bubble");
//3 dimensional array parse
    parse_textures_3D('F', gfx, buf, "right_arm");
    parse_textures_3D('H', gfx, buf, "harpoon");
    parse_textures_3D('I', gfx, buf, "bottle");
    parse_textures_3D('J', gfx, buf, "timer");
    // parse_textures_3D('L', gfx, buf, "ammo");    //puuttuu mun dnsta
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