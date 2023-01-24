project(libtestframework)
cmake_minimum_required(VERSION 3.24)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_EXPORT_COMPILE_COMMANDS true)
set (CMAKE_CXX_COMPILER /usr/bin/clang++)
add_compile_options(-std=c++20 -g -I.)

set (SRC testframework/Generator/Generator.cpp 
			testframework/Generator/GeneratorArray.cpp)
set (SRC_GUI Qt/main.cpp 
			Qt/Window/MainWindow.cpp)

add_library(testframework ${SRC})
target_compile_options(testframework PRIVATE -Wall -Wextra -Werror)

add_executable(testgenerator tests/generator.cpp)
add_dependencies(testgenerator testframework)
target_compile_options(testgenerator PRIVATE -Wall -Wextra -Werror)

add_executable(gui tests/gui.cpp)
add_dependencies(gui testframework)
target_sources(gui PRIVATE ${SRC_GUI})
target_link_libraries(gui Qt5Core Qt5Gui Qt5Widgets)
target_compile_options(gui PRIVATE -fPIC -I/usr/include/x86_64-linux-gnu/qt5)