cmake_minimum_required(VERSION 3.17)
project(game_of_life)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/libraries/SDL2-2.0.20-vc")

# SDL2
add_library(SDL2 STATIC IMPORTED)
set_target_properties(SDL2 PROPERTIES IMPORTED_LOCATION ${SDL2_PATH}/lib/x86/SDL2.lib)

add_library(SDL2_MAIN STATIC IMPORTED)
set_target_properties(SDL2_MAIN PROPERTIES IMPORTED_LOCATION ${SDL2_PATH}/lib/x86/SDL2main.lib)

# Game of life
include_directories(include)
include_directories(libraries/SDL2-2.0.20-vc/include)

add_executable(game_of_life src/main.cpp src/cell.cpp src/game.cpp src/sdl_wrappings.cpp src/renderer.cpp src/renderer.hpp src/RGB.cpp src/RGB.hpp)
target_link_libraries(game_of_life SDL2_MAIN SDL2)
