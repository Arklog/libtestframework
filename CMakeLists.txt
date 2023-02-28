project(libtestframework)
cmake_minimum_required(VERSION 3.24)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS false)

add_compile_options(-g -I. -fPIC -DDEBUG)

file(GLOB SRC source/**/*.cpp)
file(GLOB HEADERS testframework/**/*.h)

# testframework library
add_library(testframework SHARED ${SRC})
target_compile_options(testframework PRIVATE -Wall -Wextra)
target_link_libraries(testframework pthread)

install(TARGETS testframework)
install(DIRECTORY "./testframework" TYPE INCLUDE)

# tests for the generator class
add_executable(testgenerator tests/generator.cpp)
add_dependencies(testgenerator testframework)
target_link_libraries(testgenerator testframework)

# tests for the framework
add_library(testgui SHARED tests/gui.cpp)
add_dependencies(testgui testframework)
target_link_libraries(testgui testframework)

#test for ThreadWrapper
add_executable(testthread tests/thread.cpp)
add_dependencies(testthread testframework)
target_link_libraries(testthread testframework)