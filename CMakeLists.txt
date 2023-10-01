cmake_minimum_required(VERSION 3.26.0)

if (POLICY CMP0048)
  cmake_policy(SET CMP0048 NEW)
endif (POLICY CMP0048)

project(YAVE VERSION 1.0)

#compile options
option(USE_DIRECT "use direct paths instead of relative - good for testing, bad for sharing" ON)


#option 1
IF(USE_DIRECT)
set(DIRECT_DIR_P "EXPAND(YAVE_ROOT_DIR)x")
set(DIRECT_DIR "DIRECT_DIR_P(\"/\" x)")
ELSE()
set(DIRECT_DIR_P "x")
set(DIRECT_DIR "DIRECT_DIR_P(x)")
ENDIF()


IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
set(DEBUG_MODE 1)
ELSE()
set(DEBUG_MODE 0)
ENDIF()


configure_file( version_config.h.in ${CMAKE_BINARY_DIR}/generated/version_config.h )
set(VERSION_CONFIG_DIR ${CMAKE_BINARY_DIR}/generated/)

#submodules
#update
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

#add
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/glad/cmake)
add_subdirectory(external/YAAL)

# assimp options
OPTION ( ASSIMP_INSTALL "" OFF )
OPTION ( ASSIMP_WARNINGS_AS_ERRORS "" OFF )

add_subdirectory(external/assimp)

#install python requirements
find_package(Python COMPONENTS Interpreter REQUIRED)

# detect virtualenv and set Pip args accordingly
if(DEFINED ENV{VIRTUAL_ENV} OR DEFINED ENV{CONDA_PREFIX})
  set(_pip_args)
else()
  set(_pip_args "--user")
endif()

execute_process(COMMAND ${Python_EXECUTABLE} -m pip install -r ${CMAKE_SOURCE_DIR}/external/glad/requirements.txt)



#generate glad
glad_add_library(glad API gl:core=4.0)

set(YAVE_MAIN_FILES "main/config.h" "main/config.cpp" "main/render.h" "main/render.cpp")
file( GLOB_RECURSE LIB_SOURCES src/*.cpp )
file( GLOB_RECURSE LIB_HEADERS lib/*.h )
add_library( YaveAll ${LIB_SOURCES} ${LIB_HEADERS} ${YAVE_MAIN_FILES} "global.h")


add_executable( Yave main.cpp )

#end of main files


#add dependencies
list(APPEND LIBS glfw)
list(APPEND LIBS glm)
list(APPEND LIBS glad)
list(APPEND LIBS assimp)
list(APPEND LIBS YAAL)

list(APPEND EXTRA_INCLUDE_DIRS external/glfw/include)
list(APPEND EXTRA_INCLUDE_DIRS external/glm)
list(APPEND EXTRA_INCLUDE_DIRS external/glad)
list(APPEND EXTRA_INCLUDE_DIRS external/assimp/include)
list(APPEND EXTRA_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/external/assimp/include)
list(APPEND EXTRA_INCLUDE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/gladsources/glad/include)
list(APPEND EXTRA_INCLUDE_DIRS external/stb)
list(APPEND EXTRA_INCLUDE_DIRS external/YAAL)

# conio.h
IF(NOT WIN32)
list(APPEND EXTRA_INCLUDE_DIRS external)
ENDIF()

target_include_directories( Yave PUBLIC ${EXTRA_INCLUDE_DIRS} ${VERSION_CONFIG_DIR})
target_include_directories( YaveAll PUBLIC ${EXTRA_INCLUDE_DIRS} ${VERSION_CONFIG_DIR})

target_link_libraries( YaveAll ${LIBS}) 
target_link_libraries( Yave YaveAll) 

