SRC := src/Test/Test.cpp \
	   src/Test/TestFuncCmp.cpp \
	   src/Test/TestManager.cpp \
	   src/Test/TestSuite.cpp \
	   src/Gui/Window.cpp \
	   src/Gui/MainWindow.cpp \
	   src/Gui/TestWindow.cpp \
	   src/Gui/ErrorWindow.cpp

OBJ := ${SRC:.cpp=.o}

CC		:= g++
CFLAGS	:= -Werror -Wall -Wextra -ggdb -I./include -std=c++17

NAME	:= libtestframework.a

.PHONY: all re clean

all: lib

lib: ${OBJ}
	ar rcs ${NAME} ${OBJ}

test: all
	${CC} ${CFLAGS} -I./include -o $@ test.cpp -L. -ltestframework -lncurses

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

re: | clean all

clean:
	@rm -rf ${OBJ} ${NAME}
