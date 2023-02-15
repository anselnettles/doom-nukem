NAME =	editor
SRCS =	srcs/choose_to_reset_map_or_exit.c \
		srcs/close_program.c \
		srcs/copy_map_to_map_temp.c \
		srcs/create_map_temp.c \
		srcs/img1_and_img2.c \
		srcs/img1_img2_is_mouse_in_grid.c \
		srcs/img1_to_gui.c \
		srcs/img2_to_gui.c \
		srcs/img3_is_mouse_in_grid.c \
		srcs/img3_to_gui.c \
		srcs/init.c \
		srcs/initialization.c \
		srcs/map_editor.c \
		srcs/overwrite_map_file.c \
		srcs/param_to_modify.c \
		srcs/read_map.c \
		srcs/main.c \
		srcs/parse_map_file_to_arrays.c \
		srcs/save_changes.c \
		srcs/select_new_param_value.c \
		srcs/set_image_limits.c \
		srcs/set_values_for_parameters.c \
		srcs/swap_red_with_blue.c \
		srcs/tt_errors.c \
		srcs/testing_print_map.c \
		srcs/validate_buffer_format.c \
		srcs/validate_map_temp.c \
	    #srcs/overwrite_map_file.c \
		
OBJ = $(SRCS:.c=.o)
HDR = -I ./srcs
FLAGS = 
CGFLAGS = 
INCLUDES	=	-I./frameworks/SDL2.framework/Versions/A/Headers \
				-I./frameworks/SDL2_image.framework/Versions/A/Headers \
				-I./frameworks/SDL2_mixer.framework/Versions/A/Headers \
				-F./frameworks/
FRAMEWORKS	=	-F./frameworks \
				-rpath ./frameworks \
				 \
				-framework SDL2 -framework SDL2_image \
				-framework SDL2_mixer

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(CGFLAGS) $(FRAMEWORKS) $(OBJ) -o $(NAME)

.c.o: $(HEADERS)
	@gcc $(FLAGS) $(INCLUDES) $(HDR) -c $< -o $@

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(OBJ)
	@rm -rf $(NAME);

re: fclean all