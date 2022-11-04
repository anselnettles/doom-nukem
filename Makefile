# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#   Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aviholai <aviholai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/16 17:04:55 by aviholai          #+#    #+#              #
#    Updated: 2022/11/04 19:02:05 by aviholai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
### VARIABLES ###
#################

NAME			= doom-nukem

SRC				= \
				src/error_management.c\
				src/main.c\
				src/parse_level.c\
				src/utility_functions.c

OBJ				= $(SRC:.c=.o)

CFLAGS			= -Wall -Wextra -Werror -Wconversion
INC				= -I $(SDL_DIR)/include/SDL2

LISTSRC	=	$(foreach part,$(SRC), 	$(PL)		${G}| $(part)						${PR})

SDL_SRC_DIR			= SDL2-2.0.8
SDL_DIR				= libSDL2
SDL_BUILD_DIR_PATH	= $(CURDIR)/$(SDL_DIR)
SDL_CFLAGS			= `$(SDL_DIR)/bin/sdl2-config --cflags --libs`

#############
### RULES ###
#############

.SILENT:

all : $(NAME)

SDL :
	@${RUN_HEAD}
	@printf "	${PL}	${Yb}Ｅｘｔｒａｃｔｉｎｇ ＳＤＬ ａｒｃｈｉｖｅｓ．			 ${PR}"
	@printf "	${PL}		${G}| Extracting the external multimedia library.		${PR}"
	@printf "	${PL}									${PR}"
	@tar xzf SDL2-2.0.8.tar.gz
	@mkdir -p $(SDL_DIR)
	@printf "	${PL}	${Yb}Ｃｏｍｐｉｌｉｎｇ ａｎｄ ｉｎｓｔａｌｌｉｎｇ ＳＤＬ．		 ${PR}"
	@printf "	${PL}		${G}| Running external Makefile and				${PR}"
	@printf "	${PL}		${G}| installing the multimedia library.			${PR}"
	@printf "	${PL}		${G}| This will take a moment ...				${PR}${Nul}"
	@cd $(SDL_SRC_DIR); ./configure --prefix=$(SDL_BUILD_DIR_PATH); make -j6; make install

$(NAME) : $(OBJ)
	@printf "	${PL}									${PR}"
	@printf "	${PL}	${Yb}Ｃｏｍｐｉｌｉｎｇ.		 				${PR}"
	@printf "	${PL}		${G}| Creating objects and archives with the		${PR}"
	@printf "	$(PL)		${G}| following source files:				${PR}"
	@printf "$(LISTSRC)"
	@printf "	${PL}									${PR}"
	@cc $(CFLAGS) $(INC) -lm $(SDL_CFLAGS) $(OBJ) -o $(NAME)
	@printf "	${PL}									${PR}"
	@printf "	${PL}	${Yb}Ｆｉｎｉｓｈｅｄ ｂｉｎａｒｙ.					${PR}"
	@printf "	${PL}		${G}| Executable '$(NAME)' compiled with 'cc'.		${PR}"
	@printf "	${PL}									${PR}${Nul}"
	@${RUN_TAIL}

clean :
	@echo "${GN}Cleaning object files. ${Y}"
	@rm -v -f ${OBJ}
	@rm -v -f *.gch
	@rm -v -f *.bak
	@rm -v -f *~; echo "${Nul}"

fclean : clean
	@echo "${GN}Cleaning binary and debug files. ${Y}"
	@rm -v -f $(NAME)
	@rm -v -f *.dSYM
	#@rm -v -f -r $(SDL_SRC_DIR)
	#@rm -v -f -r $(SDL_DIR); echo "${Nul}"

#	Instead of a huge list, it would be nicer to get all the removed items
#	for a single line, refreshing as it moves on to the next file.

re : fclean all

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
