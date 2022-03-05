#pragma once

#include <utility>
#include <stdexcept>
#include <functional>
#include <SDL.h>

namespace SDL
{
    class SDLException : public std::runtime_error
    {
    public:
        explicit SDLException(const char *last_sdl_error = SDL_GetError());
        ~SDLException() noexcept override = default;
    };

    class ApplicationGuard
    {
    public:
        ApplicationGuard();
        ~ApplicationGuard();
    };

    template<typename ... Args>
    void init(Args &&... args)
    {
        if (SDL_Init(std::forward<Args>(args)...) != 0)
        {
            throw SDLException();
        }
    }

    template<typename T, auto create_function, auto destroy_function>
    class ManagedSDLResource
    {
    public:

        template<typename ... Args>
        explicit ManagedSDLResource(Args &&... args)
        {
            resource = create_function(std::forward<Args>(args)...);
            if (resource == nullptr)
            {
                throw SDLException();
            }
        }

        ~ManagedSDLResource()
        {
            destroy_function(resource);
        }

        operator T *() const
        {
            return resource;
        }

    private:
        T *resource;
    };

    using ManagedWindow = ManagedSDLResource<SDL_Window, SDL_CreateWindow, SDL_DestroyWindow>;
    using ManagedRenderer = ManagedSDLResource<SDL_Renderer, SDL_CreateRenderer, SDL_DestroyRenderer>;
}