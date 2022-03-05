#include "renderer.hpp"

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
    SDL_RenderFillRect(_renderer, &rect);
}

void Renderer::present()
{
    SDL_RenderPresent(_renderer);
}
