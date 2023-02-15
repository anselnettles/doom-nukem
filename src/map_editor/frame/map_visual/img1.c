// cat1 12,cat2 36, cat3 48

function(t_editor *editor, t_editor_images *images, t_elements *element_images)
{
	unsigned short int	element_x;
	unsigned short int	element_y;
	unsigned short int	index_x;
	unsigned short int	index_y;
	unsigned short int	index_param;

	//set coordinates for the first element_images
	//these coordinates are looped
	
	element_y = images->img1_y_min;
	index_y = 0;
	int i2 = 0, i1 = 0, i0 = 0; //same as element_x and element_y
	while (index_y < images->row1)
	{
		element_x = images->img1_x_min;
		index_x = 0;
		i1 = 0;
		while (index_x < images->col1)
		{
			index_param = 0;
			i0 = 0;
			while (index_param < PARAM_COUNT)
			{
				//if (map[][][i0] == <certain_char>, if...)
					//render(element_x, element_image)
				element_x = element_x + (IMG1_CATHETUS + 1);
				index_param++;
				i0++;
			}
			i1++;
			index_x++;
		}
		element_y = element_y + (IMG1_CATHETUS + 1);
		index_y++;
		i2++;
	}
	

}

int img1(t_editor *editor, t_editor_images *images, t_elements *element_images)
{
	//	element_images are in a struct
	//	SDL_LoadBMP --> *wall_full, ...
	//	.wall_full, .wall_%, 45SE, 45SW, ..., monster1-n,
	//	player_spawn, goal, sprite1, sprite2, ...
    SDL_RenderClear(editor->renderer);
	function(editor, images, element_images, element_images);
    return (0);   
}
