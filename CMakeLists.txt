cmake_minimum_required(VERSION 2.8.0)

project(YAVE)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++20 -I include/assimp ")
SET(GCC_COVERAGE_LINK_FLAGS    "-lglad -lglfw -lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl -l lib64 -lassimp")

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")


file( GLOB_RECURSE LIB_SOURCES src/*.cpp )
file( GLOB_RECURSE LIB_HEADERS lib/*.h )
add_library( Imgui ${LIB_SOURCES} ${LIB_HEADERS} )


#file( GLOB LIB_SOURCES src/YAVE/*.cpp )
#file( GLOB LIB_HEADERS lib/*.h )
#add_library( YaveLib ${LIB_SOURCES} ${LIB_HEADERS} )


add_executable( Yave main.cpp)

#target_link_libraries( Yave YaveLib )
target_link_libraries( Yave Imgui )
target_link_libraries( Yave glfw glad)
