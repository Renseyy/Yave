cmake_minimum_required(VERSION 2.8.12)

project(YAVE)

IF(WIN32)
link_libraries(-lglfw3 -lopengl32 -lglu32 -lgdi32 -lglad -lassimp.dll)
ELSE()
link_libraries(-lglad -lglfw -lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl -lassimp -lIrrKlang)
ENDIF()

#select all files under lib/ and src/
set(YAVE_MAIN_FILES "main/config.h" "main/config.cpp" "main/render.h" "main/render.cpp")
file( GLOB_RECURSE LIB_SOURCES src/*.cpp )
file( GLOB_RECURSE LIB_HEADERS lib/*.h )
file( GLOB_RECURSE LIB_HEADERS lib/*.hpp )
add_library( YaveAll ${LIB_SOURCES} ${LIB_HEADERS} ${YAVE_MAIN_FILES} "global.h")

add_executable( Yave main.cpp )

target_link_libraries( Yave YaveAll ) 
