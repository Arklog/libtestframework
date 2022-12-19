SRC := testframework/Test/Test.cpp \
	   testframework/Test/TestFuncCmp.cpp \
	   testframework/Test/TestManager.cpp \
	   testframework/Test/TestSuite.cpp \
	   testframework/Gui/Window.cpp \
	   testframework/Gui/MainWindow.cpp \
	   testframework/Gui/TestWindow.cpp \
	   testframework/Gui/ErrorWindow.cpp \
	   testframework/Utils/Functions.cpp

OBJ := ${SRC:.cpp=.o}

INC := -I. \
		-I./testframework 

CC		:= g++
CFLAGS	=	-Werror \
			-Wall \
			-Wextra \
			-ggdb \
			${INC} \
			-std=c++17 \
			${DEFINES}
DEFINES := -DMULTITHREAD #-DDEBUG

NAME	:= libtestframework.a

.PHONY: all re clean test

all: lib

lib: ${OBJ}
	ar rcs ${NAME} ${OBJ}

test: test.o all
	${CC} ${CFLAGS} ${INC} -o $@ test.o -L. -ltestframework -lncurses

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

re: | clean all

clean:
	@rm -rf ${OBJ} ${NAME} test{.o,}
