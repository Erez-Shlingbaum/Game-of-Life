#pragma once

#include "sdl_wrappings.hpp"
#include "color.hpp"

class Renderer
{
public:
    template<typename ... Args>
    explicit Renderer(Args &&... args):
            _renderer(std::forward<Args>(args)...)
    {}

    void clear();
    /*
    * From SDL docs: Alpha value used to draw on the rendering target; usually `SDL_ALPHA_OPAQUE` (255). Use SDL_SetRenderDrawBlendMode to specify how the alpha channel is used
    * */
    void set_draw_color(Color::RGB rgb, uint8_t alpha = SDL_ALPHA_OPAQUE);
    void fill_rect(const SDL_Rect &rect);
    void present();

private:
    SDL::ManagedRenderer _renderer;
};


