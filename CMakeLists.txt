cmake_minimum_required(VERSION 2.8.12)

project(YAVE)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++20 ")
SET(GCC_COVERAGE_LINK_FLAGS    "-lglad -lglfw -lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl -l lib64 -lassimp")

file( GLOB_RECURSE LIB_SOURCES src/*.cpp )
file( GLOB_RECURSE LIB_HEADERS lib/*.h )
add_library( YaveAll ${LIB_SOURCES} ${LIB_HEADERS} )

add_executable( Yave main.cpp)

target_link_libraries( Yave YaveAll )
target_link_libraries( Yave glfw glad assimp) 
