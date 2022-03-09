#include "window.hpp"

const SDL::ManagedWindow &SDL::Window::window() const
{
    return _window;
}

void SDL::Window::set_window_bordered(bool is_bordered)
{
    SDL_SetWindowBordered(_window, static_cast<SDL_bool>(is_bordered));
}
