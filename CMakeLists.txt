project(libtestframework)
set (CMAKE_CXX_STANDARD 23)
add_compile_options(-Wall -Wextra -Werror -std=c++23 -g -I.)

set (SRC testframework/Generator/Generator.cpp 
			testframework/Generator/GeneratorRange.cpp)

add_library(testframework ${SRC})

add_executable(testgenerator tests/generator.cpp)
add_dependencies(testgenerator testframework)