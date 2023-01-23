project(libtestframework)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_COMPILE_FEATURES "-Wall -Wextra -Werror -std=c++2b -fmodules-ts")
add_compile_options(-Wall -Wextra -Werror -std=c++23 -fmodules-ts -I.)

set (SRC testframework/Generator/Generator.cpp)

add_library(testframework ${SRC})