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

    ScreenDimensions get_current_display_mode()
    {
        SDL_DisplayMode display_mode{};
        if (SDL_GetCurrentDisplayMode(0, &display_mode) != 0)
        {
            throw SDLException();
        }

        return {static_cast<size_t>(display_mode.w), static_cast<size_t>(display_mode.h)};
    }
}

