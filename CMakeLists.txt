cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME JEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

project(${PROJECT_NAME})

include_directories(lib)
include_directories(lib/stb)
include_directories(src)

add_subdirectory(src/core)
add_subdirectory(src/components)
add_subdirectory(src/systems)


add_executable(${PROJECT_NAME} lib/stb/stb_image.c src/main.cpp)

include(FindPkgConfig)

pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})
set(LIBS ${LIBS} ${SDL2_LIBRARIES})

find_package(OpenGL REQUIRED OpenGL)
include_directories(${OPENGL_INCLUDE_DIRS})
set(LIBS ${LIBS} ${OPENGL_LIBRARIES})

find_package(SDL2_mixer REQUIRED)
include_directories(${SDLMIXERINCLUDE_DIR})
set(LIBS ${LIBS} ${SDLMIXER_LIBRARY})


target_link_libraries(${PROJECT_NAME} ${LIBS} SYSTEMS)
