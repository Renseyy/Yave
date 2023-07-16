cmake_minimum_required(VERSION 2.8.12)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(YAVE VERSION 1.0)

IF(WIN32)
link_libraries(-lopengl32 -lglu32 -lgdi32)
ELSE()
link_libraries(-lGL -lm -lX11 -lpthread -lXrandr -lXi -ldl -lIrrKlang)
ENDIF()

#select all files under lib/ and src/
set(YAVE_MAIN_FILES "main/config.h" "main/config.cpp" "main/render.h" "main/render.cpp")
file( GLOB_RECURSE LIB_SOURCES src/*.cpp )
file( GLOB_RECURSE LIB_HEADERS lib/*.h )
add_library( YaveAll ${LIB_SOURCES} ${LIB_HEADERS} ${YAVE_MAIN_FILES} "global.h")

add_executable( Yave main.cpp )


find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT
        )
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

#submodules
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/glad/cmake)
add_subdirectory(external/assimp)

list(APPEND EXTRA_INCLUDE_DIRS external/glfw/include)
list(APPEND EXTRA_INCLUDE_DIRS external/glm)
list(APPEND EXTRA_INCLUDE_DIRS external/assimp/include)
list(APPEND EXTRA_INCLUDE_DIRS external/stb)

target_include_directories( Yave PUBLIC ${EXTRA_INCLUDE_DIRS} )
target_include_directories( YaveAll PUBLIC ${EXTRA_INCLUDE_DIRS} )

target_link_libraries( Yave YaveAll glfw glm glad assimp) 
