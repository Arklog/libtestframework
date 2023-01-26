project(libtestframework)
cmake_minimum_required(VERSION 3.24)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_EXPORT_COMPILE_COMMANDS true)
set (CMAKE_CXX_COMPILER /usr/bin/clang++)
add_compile_options(-std=c++20 -g -I. -fPIC -DDEBUG)

file(GLOB SRC testframework/**/*.cpp)
file(GLOB SRC_GUI Qt/*.cpp
					Qt/**/*.cpp)
file(GLOB SRC_SQLITE lib/sqlite3/*.c)


# sqlite3 library
add_library(sqlite ${SRC_SQLITE})

# testframework library
add_library(testframework ${SRC})
add_dependencies(testframework sqlite)
target_link_libraries(testframework sqlite)
target_compile_options(testframework PRIVATE -Wall -Wextra -Werror)

# testframework program
add_executable(testframeworkui ${SRC_GUI})
add_dependencies(testframeworkui  testframework)
target_sources(testframeworkui PRIVATE ${SRC_GUI})
target_link_libraries(testframeworkui testframework Qt5Core Qt5Gui Qt5Widgets)
target_compile_options(testframeworkui  PRIVATE -fPIC -I/usr/include/x86_64-linux-gnu/qt5)

# tests for the generator class
add_executable(testgenerator tests/generator.cpp)
add_dependencies(testgenerator testframework)
target_link_libraries(testgenerator testframework)
target_compile_options(testgenerator PRIVATE -Wall -Wextra -Werror)

# tests for the database
add_executable(testdb tests/database.cpp)
add_dependencies(testdb testframework)
target_link_libraries(testdb testframework)

add_library(testgui SHARED tests/gui.cpp)
add_dependencies(testgui testframework)
target_link_libraries(testgui testframework)