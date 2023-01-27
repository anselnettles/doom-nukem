#include "../includes/map_editor.h"

int map_editor(char *map_file, t_map *dimensions)
{
    t_editor        editor;
    t_mouse         mouse;
    t_editor_images lim;
    short int       quit;

    set_image_limits(&lim);
    read_map(map_file, dimensions, &lim);
    //testing_print_map(*dimensions, *lim);
    if (init(&editor) != 1)
    {
        tt_errors("main: init() fail");
        close_program(&editor);
    }

    img1_to_gui(&editor, &mouse, &lim); 
    SDL_SetRenderDrawColor(editor.renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderPresent(editor.renderer);  

    quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&editor.event))
        {
            if (editor.event.type == SDL_QUIT)
                quit = 1;
            if (editor.event.type == SDL_MOUSEMOTION)
                SDL_GetMouseState(&mouse.x, &mouse.y);
            if (get_m1_pressed_map_element(&mouse, dimensions, &lim) == 1)  //rename properly, see readme.txt
            {
                img1_and_img2(&editor, dimensions, &mouse, &lim);    //rename properly, this also contains img3_to_gui

            }
            if (get_m1_pressed_img3_grid_element(&mouse, dimensions, &lim) == 1)    //rename properly, see readme.txt
            {
                /*  param_to_modify(img2) and map_x/map_y(img3) are correct. map_x/map_y must remain linked
                    to img1. Make new element identifier for img3. May need to alter get_m1_pressed_img3_grid_element()
                    to replace map_x/map_y with img3-related map_x/map_y    */
                printf("map_x %d | map_y %d\n", lim.map_x, lim.map_y);
                printf("img2 param_to_modify: %d\n", dimensions->param_to_modify);
                //select_new_param_value();
            }
                
            if (editor.event.button.button == SDL_BUTTON_RIGHT) //double executes now. Insert separately into img1-img2 & img3 functions?
            {
                printf("M2 was pressed\n");
                lim.img_switch = 1;
                SDL_RenderClear(editor.renderer);
                SDL_SetRenderDrawColor(editor.renderer, 0x00, 0x00, 0x00, 0x00);
                img1_to_gui(&editor, &mouse, &lim);
                SDL_RenderPresent(editor.renderer);
            }
            if (editor.event.type == SDL_KEYDOWN)   
            {
                if (editor.event.key.keysym.sym == SDLK_ESCAPE)
                    close_program(&editor);
                // key presses
            }    
        } 
    }
    return (0);
}


/*  BU img1_img2 before a separate function

    if (editor.event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (editor.event.button.button == SDL_BUTTON_LEFT && lim.img_switch == 1)
        {
            printf("A grid was clicked. img_switch: %d\n", lim.img_switch);
            SDL_RenderClear(editor.renderer);
            SDL_SetRenderDrawColor(editor.renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(&editor, &mouse, &lim); 
            img2_to_gui(&editor, &lim);
            SDL_RenderPresent(editor.renderer);
            printf("map_x %d | map_y %d\n", lim.map_x, lim.map_y);
            lim.img_switch = 2;
            dimensions->x_to_modify = lim.map_x;
            dimensions->y_to_modify = lim.map_y;
            printf("Operations done. img_switch: %d\n", lim.img_switch);
        }
        else if (editor.event.button.button == SDL_BUTTON_LEFT && lim.img_switch == 2)
        {
            printf("A grid was clicked. img_switch: %d\n", lim.img_switch);
            SDL_RenderClear(editor.renderer);
            SDL_SetRenderDrawColor(editor.renderer, 0x00, 0x00, 0x00, 0x00);
            img1_to_gui(&editor, &mouse, &lim); 
            img2_to_gui(&editor, &lim);
            printf("map_x %d | map_y %d\n", lim.map_x, lim.map_y);
            dimensions->param_x_to_modify = lim.map_x;
            dimensions->param_y_to_modify = lim.map_y;
            param_to_modify(dimensions);
            img3_to_gui(&editor, &lim, dimensions);

            SDL_RenderPresent(editor.renderer);
            lim.img_switch = 3;
            printf("Operations done. img_switch: %d\n", lim.img_switch);
        }
        //  third grid is opened correctly
        //see readme.txt
        else if (editor.event.button.button == SDL_BUTTON_RIGHT)
        {
            printf("M2 was pressed\n");
            lim.img_switch = 1;
            SDL_RenderClear(editor.renderer);
           SDL_SetRenderDrawColor(editor.renderer, 0x00, 0x00, 0x00, 0x00);
           img1_to_gui(&editor, &mouse, &lim);
           SDL_RenderPresent(editor.renderer);
       }
   }

*/