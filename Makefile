SRC := src/Test.cpp \
	   src/TestFuncCmp.cpp \
	   src/TestManager.cpp \
	   src/TestSuite.cpp \
	   src/Window.cpp \
	   src/MainWindow.cpp \
	   src/TestWindow.cpp \
	   src/ErrorWindow.cpp

OBJ := ${SRC:.cpp=.o}

CC		:= g++
CFLAGS	:= -Werror -Wall -Wextra -ggdb -I./include

NAME	:= libtestframework.a

.PHONY: all re clean

all: lib

lib: ${OBJ}
	ar rcs ${NAME} ${OBJ}

test: all
	${CC} ${CFLAGS} -o $@ test.cpp -L. -ltestframework -lncurses

%.o: %.cpp
	${CC} ${CFLAGS} -c $< -o $@

re: | clean all

clean:
	@rm -rf ${OBJ} ${NAME}
