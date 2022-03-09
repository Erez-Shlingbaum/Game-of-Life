#include <SDL.h>
#include "game.hpp"
#include "sdl_wrappings.hpp"
#include "constants.hpp"


int main(int argc, char **argv)
{
    SDL::ApplicationGuard sdl_guard{};

    Game game{"Game of Life", Consts::CELL_WIDTH, Consts::CELL_HEIGHT};
    game.run();
    return 0;
}
