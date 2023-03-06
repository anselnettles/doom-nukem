# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#   Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 17:04:55 by aviholai          #+#    #+#              #
#    Updated: 2023/02/27 09:38:42 by aviholai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ılılılllıılılıllllıılılllıllı▐ VARIABLES ▐ılılılllıılılıllllıılılllıllı#

NAME				=	doom-nukem

CC					=	gcc
FILES				=	\
						controls_keyboard\
						controls_mouse\
						editor_choose_to_reset_map_or_exit\
						editor_clear_surface \
						editor_close_program \
						editor_draw_grid_of_squares \
						editor_draw_one_square \
						editor_element_colour \
						editor_img1_and_img2 \
						editor_img1_img2_is_mouse_in_grid \
						editor_img3_is_mouse_in_grid \
						editor_is_element_bloated \
						editor_map_editor \
						editor_param_to_modify \
						editor_parse_textures \
						editor_parse_textures_malloc \
						editor_pix_put \
						editor_read_map \
						editor_select_new_param_value \
						editor_set_image_limits \
						editor_set_values_for_parameters \
						editor_swap_red_with_blue \
						editor_tt_errors \
						editor_testing_print_map \
						editor_validate_buffer_format \
						editor_validate_map \
						editor_validate_outer_walls \
						error_management \
						graphic_render \
						graphic_render_animations \
						graphic_render_draw \
						graphic_render_filters \
						graphic_render_hud \
						graphic_render_overlay \
						graphic_render_raycast \
						graphic_render_timeline \
						main \
						utilities_graphic \
						utilities_movement \
						utilities_system

SRC					=	$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ					=	$(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_DIR				=	obj
LISTSRC				=	$(foreach part,$(SRC), 	$(PL)		${G}| $(part)\n)
FLAGS				=	-g -O3 #-Wall -Wextra -Werror
HEADER				=	-I./src
LIBFT				=	libft/

OS = $(shell uname)
ifeq ($(OS), Linux)
CGFLAGS				=	`sdl2-config --cflags --libs` -lSDL2 -lSDL2_image \
						-lSDL2_mixer -lSDL2_ttf -lm
else
CGFLAGS				=	-framework OpenGL -framework AppKit
INC					=	-I./frameworks/SDL2.framework/Versions/A/Headers \
						-I./frameworks/SDL2_ttf.framework/Versions/A/Headers \
						-I./frameworks/SDL2_image.framework/Versions/A/Headers \
						-I./frameworks/SDL2_mixer.framework/Headers \
						-F./frameworks/
FRAMEWORKS			=	-F./frameworks \
						-rpath ./frameworks \
						-framework OpenGL -framework AppKit -framework OpenCl \
						-framework SDL2 -framework SDL2_ttf \
						-framework SDL2_image -framework SDL2_mixer
endif

#ılılılllıılılıllllıılılllıllı▐ RULES ▐ılılılllıılılıllllıılılllıllı#

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	@make -C $(LIBFT)
	@${RUN_HEAD}
	@printf "	${PL}									${PR}"
	@printf "	${PL}	${Yb}Ｃｏｍｐｉｌｉｎｇ.		 				${PR}"
	@printf "	${PL}		${G}| Creating objects and archives with the		${PR}"
	@printf "	$(PL)		${G}| following source files:				${PR}${Nul}"
	@printf "$(LISTSRC)"
	@printf "	${PL}									${PR}${Nul}"
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) $(CGFLAGS) $(FRAMEWORKS) libft/libft.a
	@printf "	${PL}									${PR}"
	@printf "	${PL}	${Yb}Ｆｉｎｉｓｈｅｄ ｂｉｎａｒｙ.					${PR}"
	@printf "	${PL}		${G}| Executable '$(NAME)' compiled with '$(CC)'.		${PR}"
	@printf "	${PL}									${PR}${Nul}"
	@${RUN_TAIL}

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

obj/%.o: src/%.c
	@$(CC) -o $@ $(FLAGS) $(SPEED) $(HEADER) $(INC) -c $^

clean :
	@echo "${GN}Cleaning object files. ${Y}"
	@rm -v -rf ${OBJ_DIR}
	@rm -v -f *.gch
	@rm -v -f *.bak
	@rm -v -f *~; echo "${Nul}"

fclean : clean
	@echo "${GN}Cleaning binary and debug files. ${Y}"
	@rm -v -f $(NAME)
	@rm -v -f *.dSYM
	@echo "${Nul}"

#	Instead of a huge list, it would be nicer to get all the removed items
#	for a single line, refreshing as it moves on to the next file.

re : fclean all

#ılılılllıılılıllllıılılllıllı▐ VISUAL VARIABLES ▐ılılılllıılılıllllıılılllıllı#

#	Colors and visual effects. Used for more clearer visual representation.
#	'Nul' stand for "no color", 'Y' for yellow, 'G' for gray,
#	'DG' for dark gray, 'R' for red and 'GN' for green. 'PL' stand for
#	"pillar left" and 'PR' for "pillar right".

Nul		=	\033[0m
Yb		=	\033[1;33m
Y		=	\033[0;33m
G		=	\033[0;37m
R		=	\033[1;31m
GN		=	\033[1;32m

PL		=	\033[1;31m▒▒▒▒░░
PR		=	\033[1;31m      ▒▒▒▒\n

#	The ASCII art used for enhancing the user experience. Header and footer
#	are called upon rule '$(NAME)' start and end.

RUN_HEAD =	@echo "${R}\n" \
			"▒▒░░                                                                                          ░░▒▒\n"\
			"  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n"\
			"  ▒▒██████████████████████████████████████████████████████████████████████████████████████▓▓██░░\n"\
			"  ░░▒ aviholai@student.hive.fi ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒   /|,_ _ _ |  |\ | _ |-|-| _  _  ▒▒░░\n"\
			"  ▒▒▒            anselnettl.es ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒  /-|||_\(/_|  | \|(/_|_|_|(/__\  ▒▒░░\n"\
			"  ░░▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░\n"\
			"  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒░░▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n"\
			"    ░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░\n"\
			"	▒▒▒▒▒▒                               ▓▓▒▒██▓▓░░                             ▓▓▒▒▒▒\n"\
			"    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▒▒▒▒▒▒▒▒▒▒░░░░\n"\
			"  ▒▒▒▒▒▒▓▓▒▒▓▓▒▒▒▒▓▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▒▒▒▒▓▓▒▒▓▓▒▒▒▒▒▒▒▒▒▒\n"\
			"  ▒▒▒▒▒▓▓▒▒▓▓▓▓▒▒▒▒▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▒▒▒▒▓▓▒▒▒▒▓▓▒▒▒▒▒▒▒\n"\
			"  ░░   ▒▒▒▒░░									    ░░▒▒▒▒     ░░\n"\
			"	▒▒▒▒░░									      ▒▒▒▒"

RUN_TAIL =	@echo "${R}	▒▒▒▒░░               ██                          ██                           ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░                 ██████████████████████████                             ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░                   ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                               ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░                     ▓▓      ██      ▓▓                                 ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░                   ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                               ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░                     ▓▓              ▓▓                                 ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░                     ▓▓              ▓▓                                 ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░                     ▓▓              ▓▓                                 ▒▒▒▒\n"\
			"${R}	▒▒▒▒░░           $(GN)▒▒        ${R}▓▓              ▓▓        $(GN)▒▒                       ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░   $(GN)▒▒      ▒▒        ${R}▓▓              ▓▓      $(GN)▒▒▒▒      ▒▒               ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░   $(GN)▒▒    ▒▒▒▒        ${R}▓▓              ▓▓      $(GN)▒▒▒▒▒▒    ▒▒               ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░   $(GN)▒▒▒▒  ▒▒▒▒▒▒      ${R}▓▓              ▓▓    $(GN)▒▒▒▒▒▒▒▒▒▒  ▒▒▒▒             ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░ $(GN)▒▒▓▓▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒░░▒▒░░░░░░░░▒▒░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒           ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░ $(GN)▒▒▓▓▒▒░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒           ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░ $(GN)▒▒░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒░░░░░░▒▒░░░░░░░░░░▒▒░░░░░░░░▒▒▒▒▒▒         ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░ $(GN)░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░▒▒       ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░ $(GN)░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒░░░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒     ${R}▒▒▒▒\n"\
			"${R}    $(GN)░░ ${R}▒▒▒▒░░ $(GN)░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░▒▒░░░░░░░░░░▒▒▒▒▒▒▒▒ ${R}▒▒▒▒\n"\
			"${R}  $(GN)▒▒▒▒ ${R}▒▒▒▒░░ $(GN)░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒░░░░░░░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░▒▒▒▒░░▒▒▒▒▒ ${R}▒▒▒▒ $(GN)░░\n"\
			"${R}  $(GN)▒▒▒▒ ${R}▒▒▒▒░░ $(GN)░▒▒▒▒░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒ ${R}▒▒▒▒ $(GN)▒▒\n"\
			"${R}  $(GN)▓▓░░ ${R}▒▒▒▒░░ $(GN)▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▒▒▒▒▒ ${R}▒▒▒▒ $(GN)▓▓\n"\
			"${R}    $(GN)▓▓ ${R}▒▒▒▒░░ $(GN)▒▒▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓ ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░ $(GN)▓▓▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓     ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░   $(GN)▒▒▓▓▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒░░▒▒▓▓▓▓         ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░       $(GN)▒▒▓▓▓▓▓▓▒▒▒▒░░░░░░░░░░░░░░░░░░░░░░░░░░▒▒▒▒▒▒▓▓▓▓▓▓▓▓             ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░               $(GN)▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓                     ${R}▒▒▒▒\n"\
			"${R}	▒▒▒▒░░									      ▒▒▒▒"

#	The '.PHONY' target exists to avoid conflict with files of the same name.

.PHONY: all clean fclean re
