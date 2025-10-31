#########################################################
#------------------- SOURCE FILES ----------------------#

HEADER			= ${addprefix ${HEADER_DIR}, ${HEADER_FILE}}
HEADER_DIR		= include/
HEADER_FILE		= main.hpp glad/glad.hpp KHR/khrplatform.hpp

OBJ_DIR 		= obj/
OBJ 			= ${patsubst ${SRC_DIR}%.cpp, ${OBJ_DIR}%.o, ${SRC}}

SRC_DIR			= srcs/
SRC				=	${addprefix ${SRC_DIR}${SRC_MAIN_DIR}, ${addsuffix .cpp, ${SRC_MAIN_FILE}}} \
					${addprefix ${SRC_DIR}${SRC_DEP_DIR}, ${addsuffix .cpp, ${SRC_DEP_FILE}}} 

SRC_MAIN_DIR	=	main/
SRC_MAIN_FILE	=	main

SRC_DEP_DIR		= dependencies/
SRC_DEP_FILE	= glad

NAME = OpenGL_test

CC = c++ -g3
CFLAGS = -Wall -Wextra -Werror -Wunreachable-code -Ofast
INCLUDE = -I${HEADER_DIR}
LINK = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl

all:	${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${INCLUDE} ${LINK} -o ${NAME}

${OBJ_DIR}:
	@mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o: ${SRC_DIR}%.cpp ${HEADER} Makefile | ${OBJ_DIR}
	@ mkdir -p ${dir $@}
	${CC} ${CFLAGS} -DPROGRAM_NAME='"${NAME}"' ${INCLUDE} -c $< -o $@

clean:
	rm -rf ${OBJ_DIR}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re