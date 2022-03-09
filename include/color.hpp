#pragma once

#include <cstdint>

namespace Color
{
    struct RGB
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
    };

    constexpr RGB RED{255, 0, 0};
    constexpr RGB GREEN{0, 255, 0};
    constexpr RGB BLUE{0, 0, 255};
}