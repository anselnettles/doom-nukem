# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpaaso <tpaaso@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/04 13:56:16 by tpaaso            #+#    #+#              #
#    Updated: 2023/01/27 16:29:00 by tpaaso           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#ılılılllıılılıllllıılılllıllı▐ VARIABLES ▐ılılılllıılılıllllıılılllıllı#

NAME				=	doom-nukem

CC					=	gcc
FILES				=	\
						event\
						init\
						main\
						pthread_ray\
						read\
						utility\

SRC					=	$(addprefix src/, $(addsuffix .c, $(FILES)))
OBJ					=	$(addprefix obj/, $(addsuffix .o, $(FILES)))
OBJ_DIR				=	obj
LISTSRC				=	$(foreach part,$(SRC), 	$(PL)		${G}| $(part)\n)
FLAGS				=	-Wall -Wextra -Werror -O3 -g
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


.PHONY: all clean fclean re