#pragma once

#include <utility>
#include "sdl_wrappings.hpp"

namespace SDL
{
    class Window
    {
    public:
        template<typename ... Args>
        explicit Window(Args &&... args):
                _window(std::forward<Args>(args)...)
        {}

        [[nodiscard]] const ManagedWindow &window() const;
        void set_window_bordered(bool is_bordered);

    private:
        ManagedWindow _window;
    };
}
