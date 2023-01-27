NAME =	editor
SRCS =	srcs/main.c srcs/tt_errors.c srcs/read_map.c srcs/map_editor.c srcs/init.c \
		srcs/close_program.c srcs/set_image_limits.c \
		srcs/get_m1_pressed_map_element.c srcs/img1_and_img2.c \
		srcs/img1_to_gui.c srcs/img2_to_gui.c srcs/img3_to_gui.c srcs/get_m1_pressed_img3_grid_element.c \
		srcs/param_to_modify.c \
		srcs/testing_print_map.c \
	   #save_map.c \
		
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