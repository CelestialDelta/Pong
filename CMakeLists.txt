cmake_minimum_required(VERSION 3.5.1 FATAL_ERROR)

set(PROJECT_NAME pong)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(GLM_INCLUDE_DIR /usr/include/glm)
#set(SDL2_INCLUDE_DIR /usr/include)
set(SDL2_GFX_INCLUDE_DIR /usr/local/include)
#set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu/libSDL2.a)
set(SDL2_GFX_LIBRARY /usr/local/lib/libSDL2_gfx.a)

project(${PROJECT_NAME})

find_package(SDL2 REQUIRED)

add_executable(
	${PROJECT_NAME}
	src/main.cpp
	src/clock.cpp
	src/game.cpp
	src/object.cpp
	)

include_directories(
	${PROJECT_BINARY_DIR}
	${SDL2_INCLUDE_DIR}
	${SDL2_GFX_INCLUDE_DIR}
	${GLM_INCLUDE_DIR}
	)

target_link_libraries(
	${PROJECT_NAME}
	${SDL2_LIBRARY}
	${SDL2_GFX_LIBRARY}
	)
