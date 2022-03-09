#include "renderer.hpp"

namespace SDL
{
    const ManagedRenderer &Renderer::renderer() const
    {
        return _renderer;
    }

    void Renderer::clear()
    {
        SDL_RenderClear(_renderer);
    }

    void Renderer::set_draw_color(const Color::RGB rgb, const uint8_t alpha)
    {
        SDL_SetRenderDrawColor(_renderer, rgb.red, rgb.green, rgb.blue, alpha);
    }

    void Renderer::fill_rect(const SDL_Rect &rect)
    {
        // TODO error check
        SDL_RenderFillRect(_renderer, &rect);
    }

    void Renderer::present()
    {
        SDL_RenderPresent(_renderer);
    }

    ScreenDimensions Renderer::get_output_size()
    {
        int screen_width, screen_height;
        // TODO: error check
        SDL_GetRendererOutputSize(_renderer, &screen_width, &screen_height);
        return ScreenDimensions{static_cast<size_t>(screen_width), static_cast<size_t>(screen_height)};
    }
}
