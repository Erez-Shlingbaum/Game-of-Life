#include <stdexcept>
#include "SDL.h"
#include "sdl_wrappings.hpp"

namespace SDL
{
    SDLException::SDLException(const char *last_sdl_error) :
            std::runtime_error(last_sdl_error)
    {}

    ApplicationGuard::ApplicationGuard()
    {
        SDL::init(SDL_INIT_EVERYTHING);
    }

    ApplicationGuard::~ApplicationGuard()
    {
        SDL_Quit();
    }
}

