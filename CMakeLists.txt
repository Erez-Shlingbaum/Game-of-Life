cmake_minimum_required(VERSION 3.17)
project(game_of_life)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/libraries/SDL2-2.0.20-vc")

# SDL2
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory(SDL)

# Game of life
include_directories(include)

add_executable(game_of_life src/main.cpp src/cell.cpp src/game.cpp src/sdl_wrappings.cpp src/renderer.cpp src/window.cpp)
target_link_libraries(game_of_life SDL2main SDL2-static)
