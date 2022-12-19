SRC := src/Test/Test.cpp \
	   src/Test/TestFuncCmp.cpp \
	   src/Test/TestManager.cpp \
	   src/Test/TestSuite.cpp \
	   src/Gui/Window.cpp \
	   src/Gui/MainWindow.cpp \
	   src/Gui/TestWindow.cpp \
	   src/Gui/ErrorWindow.cpp \
	   src/Utils/Functions.cpp

OBJ := ${SRC:.cpp=.o}

INC := -I. \
		-I./testframework 

CC		:= g+Funtions
CFLAGS	:=	-Werror \
			-Wall \
			-Wextra \
			-ggdb \
			${INC} \
			-std=c++17 \
			#-DDEBUG

NAME	:= libtestframework.a

.PHONY: all re clean test

all: lib

lib: ${OBJ}
	ar rcs ${NAME} ${OBJ}

test: test.o all
	${CC} ${CFLAGS} ${INC} -o $@ test.o ${OBJ} -L. -ltestframework -lncurses

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

re: | clean all

clean:
	@rm -rf ${OBJ} ${NAME} test
