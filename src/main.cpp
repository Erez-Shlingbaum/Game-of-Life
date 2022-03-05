#include <SDL.h>
#include "cell.hpp"
#include "game.hpp"
#include "sdl_wrappings.hpp"


int main(int argc, char **argv)
{
    SDL::ApplicationGuard sdl_guard{};

    Game game{"Game of Life", SCREEN_WIDTH, SCREEN_HEIGHT, CELL_WIDTH, CELL_HEIGHT};
    game.run();
    return 0;
}
